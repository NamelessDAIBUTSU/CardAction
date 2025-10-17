// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyManager.h"

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// エネミーの登録 / 解除
void AEnemyManager::RegistEnemy(AEnemyBase* Enemy)
{
	// 登録済みの場合は抜ける
	if (Enemies.Find(Enemy) != INDEX_NONE)
		return;

	Enemies.Add(Enemy);
}
void AEnemyManager::UnRegistEnemy(AEnemyBase* Enemy)
{
	// 登録されていない場合は抜ける
	if (Enemies.Find(Enemy) == INDEX_NONE)
		return;

	// どこかのループで引っかかると厄介なので逆順で
	for (int i = Enemies.Num() - 1; i >= 0; --i)
	{
		if (Enemies[i] == Enemy)
		{
			Enemies.RemoveAt(i);
			return;
		}
	}
}

// エネミーの全解除
void AEnemyManager::UnRegistAllEnemies()
{
	Enemies.Empty();
}

// エネミーが1人でも生きているか
bool AEnemyManager::IsAliveAnyEnemy()
{
	for (int i = Enemies.Num() - 1; i >= 0; --i)
	{
		if (Enemies[i]->IsDead() == false)
			return true;
	}

	return false;
}

// 全エネミーが開始可能状態か
bool AEnemyManager::IsAllEnemyReady()
{
	for (int i = Enemies.Num() - 1; i >= 0; --i)
	{
		if (Enemies[i]->IsReady() == false)
			return false;
	}

	return true;
}

