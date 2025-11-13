// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "Weapon_ShortSword.generated.h"

/// <summary>
/// 武器：目の前の1マスを攻撃するソード。
/// </summary>
UCLASS()
class CARDACTION_API AWeapon_ShortSword : public AWeaponActorBase
{
	GENERATED_BODY()
	
public:
	// プレイヤーによる攻撃アクション時処理
	virtual void OnAttack() override;
};
