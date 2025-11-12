// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include <Enemy/EnemyAttackBase.h>
#include "ElectricEyeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AElectricEyeEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AElectricEyeEnemy();

public:
	// プレイヤーへの回転はしない
	virtual bool CanRotate() override { return false; }

	// 開始準備ができているか
	virtual bool IsReady() const override { return bIsReady && bCanCardSelect; }

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnSetReady();


public:
	// 何秒で準備完了とするか
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartReadySec = 2.f;

	// 何秒で移動をするか
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSec = 1.f;

	// 生成するエレクトリックサンダー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<AEnemyAttackBase> AttackClass;

private:
	// カードセレクト画面に遷移してよいか
	bool bCanCardSelect = false;;

	FTimerHandle TimerHandle;
};
