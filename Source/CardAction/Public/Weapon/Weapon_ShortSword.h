// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "Weapon_ShortSword.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AWeapon_ShortSword : public AWeaponActorBase
{
	GENERATED_BODY()
	
public:
	// �v���C���[�ɂ��U���A�N�V����������
	virtual void OnAttack() override;
};
