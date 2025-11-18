// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Weapon_IceCube.generated.h"

/// <summary>
/// 武器：アイスキューブ。直線移動 / 反射 / 敵貫通 / 時間でスケールが小さくなっていき一定以下で消滅
/// </summary>
UCLASS()
class CARDACTION_API AWeapon_IceCube : public AWeaponActorBase
{
	GENERATED_BODY()
	
public:
	AWeapon_IceCube();

public:
	virtual void Tick(float DeltaSec) override;

protected:
	virtual void BeginPlay() override;

public:
	// 初期化
	virtual void Initialize() override;

public:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTurn(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

private:
	// 回転更新
	void UpdateRotate(float DeltaSec);

	// 移動更新
	void UpdateMove(float DeltaSec);

	// スケール更新
	void UpdateScale(float DeltaSec);

	// 現在のスケール, 移動スピードで消滅させるか判定
	void UpdateCheckDestroy();


public:
	// 1秒での回転角
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotateDeg = 360.f;

	// 敵と接触時の1秒での回転角
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotateDegOnAttack = 720.f;

	// 元の回転角まで戻すための減少スピード
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecreaseDegSpeed = 30.f;

	// 1秒での移動量(マス)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveCell = 2.f;

	// 接触時減少する移動速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecreaseMoveSpeed = 100.f;
	
	// 消滅する境界スケール
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DestroyScale = 0.2f;

	// 毎フレーム減少するスケール
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecreaseScaleSpeed = 0.05f;

	// 接触時減少するスケール
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LostScale = 0.2f;

public: /* Component */
	// 移動制御コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UProjectileMovementComponent* ProjectileMoveComp;

	// 当たり判定コンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollisionComp = nullptr;

	// 移動反転用当たり判定コンポーネント
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereCollisionComp = nullptr;

private:
	// 1フレームでの回転スピード
	UPROPERTY()
	float RotateSpeed = 0.f;

	// 1フレームでの移動スピード
	UPROPERTY()
	float MoveSpeed = 0.f;

	// 現在の進行方向
	UPROPERTY()
	FVector CurrentDirection = FVector::Zero();

	// 当たり判定重複回避用キャッシュ
	UPROPERTY()
	AActor* OverlapActorCache = nullptr;
};
