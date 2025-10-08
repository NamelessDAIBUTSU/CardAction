// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyAttackBase.h"
#include <Components/SphereComponent.h>
#include <NiagaraSystem.h>
#include "PumpkinBomb.generated.h"

/// <summary>
/// パンプキンエネミーが発生させる、プレイヤーに向かって放物線上に飛んでいく弾
/// </summary>
UCLASS()
class CARDACTION_API APumpkinBomb : public AEnemyAttackBase
{
	GENERATED_BODY()
	
public:
	APumpkinBomb();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION()
	void OnHitGridCell(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	// 移動に必要なパラメータの設定
	void Setup(FVector Position);

public:
	// 爆発エフェクト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	UParticleSystem* ExplosionParticle = nullptr;

public: /* 移動 */
	// 何秒で落下するか
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float FallSec = 0.5f;
	// 放物線の最高点
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float ZPoint = 300.f;
	// 重力加速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float Gravity = 980.f;

private:
	// 当たり判定
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* SphereComp = nullptr;

	// 目標地点
	UPROPERTY(VisibleAnywhere, Category = "Move")
	FVector TargetPosition = FVector::Zero();
	// 開始地点
	UPROPERTY(VisibleAnywhere, Category = "Move")
	FVector StartPosition = FVector::Zero();
	// 初速度
	UPROPERTY(VisibleAnywhere, Category = "Move")
	FVector InitialVelocity = FVector::Zero();

	// 経過時間
	UPROPERTY(VisibleAnywhere, Category = "Move")
	float ElapsedSec = 0.f;
};
