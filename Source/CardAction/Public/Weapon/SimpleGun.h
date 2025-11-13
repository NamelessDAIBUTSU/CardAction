// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "SimpleGun.generated.h"

/// <summary>
/// オミット予定
/// </summary>
UCLASS()
class CARDACTION_API ASimpleGun : public AWeaponActorBase
{
	GENERATED_BODY()
	
public: /* AWeaponActorBase */
	// 弾の生成
	virtual void OnAttack() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASimpleProjectile> BPProjectile;
};
