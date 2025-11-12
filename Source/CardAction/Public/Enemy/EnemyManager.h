// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class CARDACTION_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// エネミーの登録 / 解除
	void RegistEnemy(AEnemyBase* Enemy);
	void UnRegistEnemy(AEnemyBase* Enemy);

	// 全エネミーの解除
	void UnRegistAllEnemies();

	// エネミーが1人でも生きているか
	bool IsAliveAnyEnemy();

	// 全エネミーが開始可能状態か
	bool IsAllEnemyReady();

	// 全エネミーの取得
	TArray<AEnemyBase*> GetEnemyList() const { return EnemyList; }

	// 指定座標のエネミーを取得
	AEnemyBase* GetEnemy(FCoord Coord);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<AEnemyBase*> EnemyList;
};
