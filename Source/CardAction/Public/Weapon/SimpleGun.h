// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "SimpleGun.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API ASimpleGun : public AWeaponActorBase
{
	GENERATED_BODY()
	
public: /* AWeaponActorBase */
	// íeÇÃê∂ê¨
	virtual void OnAttack() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASimpleProjectile> BPProjectile;
};
