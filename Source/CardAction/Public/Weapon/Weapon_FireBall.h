// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Weapon_FireBall.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AWeapon_FireBall : public AWeaponActorBase
{
	GENERATED_BODY()
	
public:
	AWeapon_FireBall();

public:
	virtual void Tick(float DeltaSec) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);


public:
	// Hit時のカスケード
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UParticleSystem* HitEffect;
	// 本体カスケード
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UParticleSystem* BodyEffect;
	// 発射時のカスケード
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UParticleSystem* ShockWaveEffect;

	// 移動制御コンポーネント
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMoveComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereCollisionComp = nullptr;

	// 加速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float AccelRate =  2500.f;

private:
	// カスケードを再生するコンポーネント
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UParticleSystemComponent* ParticleComp;
};
