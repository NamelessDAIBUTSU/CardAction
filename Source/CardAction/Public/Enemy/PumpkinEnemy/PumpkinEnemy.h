// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include <Enemy/EnemyAttackBase.h>
#include "PumpkinEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API APumpkinEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	APumpkinEnemy() {};

protected:
	virtual void BeginPlay() override;

public:
	// 回転可能か
	virtual bool CanRotate() override;

public:
	// 生成するパンプキン爆弾
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<AEnemyAttackBase> AttackClass;
};
