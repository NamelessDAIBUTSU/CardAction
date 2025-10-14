// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "Weapon_ThrowKnife.generated.h"

/**
 * 
 */
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

public:
	// �ړ�����R���|�[�l���g
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMoveComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereCollisionComp = nullptr;

	// ���x
	UPROPERTY(VisibleAnywhere, Category = "Move")
	float Verocity = 2000.f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Move")
	FVector2D GeneratedCoord = FVector2D::Zero();
};
