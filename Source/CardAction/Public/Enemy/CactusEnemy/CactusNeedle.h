// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyAttackBase.h"
#include "CactusNeedle.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API ACactusNeedle : public AEnemyAttackBase
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	// 初期化
	void Setup();

public:
	// 何秒で攻撃判定を出すか
	UPROPERTY(EditAnywhere)
	float GoalSec = 0.6f;

	// 最終スケール
	UPROPERTY(EditAnywhere)
	FVector GoalScale = FVector(1.5f);

	// 回転スピード/s
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 120.f;

	// ダメージ処理時のカスケード
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* DamageEffect;

private:
	float ElapsedSec = 0.f;

	// スケールスピード
	FVector ScaleSpeed = FVector::Zero();
};
