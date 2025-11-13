// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "Weapon_ThrowKnife.generated.h"

/// <summary>
/// 武器：直線に飛ぶナイフ。オミット予定
/// </summary>
UCLASS()
class CARDACTION_API AWeapon_ThrowKnife : public AWeaponActorBase
{
	GENERATED_BODY()
	
public:
	AWeapon_ThrowKnife();

public:
	virtual void Tick(float DeltaSec) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:
	// 移動制御コンポーネント
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMoveComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereCollisionComp = nullptr;

	// 速度
	UPROPERTY(VisibleAnywhere, Category = "Move")
	float Verocity = 2000.f;
};
