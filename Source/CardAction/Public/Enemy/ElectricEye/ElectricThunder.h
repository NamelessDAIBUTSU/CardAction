// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyAttackBase.h"
#include "ElectricThunder.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AElectricThunder : public AEnemyAttackBase
{
	GENERATED_BODY()
	
public:
	AElectricThunder();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSec) override;

public:
	// エフェクト再生時のコールバック
	UFUNCTION()
	void OnPlayEffect();

	// エフェクト終了時のコールバック
	UFUNCTION()
	void OnAttack();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ThunderEffect = nullptr;
};
