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

// �G�l�~�[�̓o�^ / ����
void AEnemyManager::RegistEnemy(AEnemyBase* Enemy)
{
	// �o�^�ς݂̏ꍇ�͔�����
	if (EnemyList.Find(Enemy) != INDEX_NONE)
		return;

	EnemyList.Add(Enemy);
}
void AEnemyManager::UnRegistEnemy(AEnemyBase* Enemy)
{
	// �o�^����Ă��Ȃ��ꍇ�͔�����
	if (EnemyList.Find(Enemy) == INDEX_NONE)
		return;

	// �ǂ����̃��[�v�ň���������Ɩ��Ȃ̂ŋt����
	for (int i = EnemyList.Num() - 1; i >= 0; --i)
	{
		if (EnemyList[i] == Enemy)
		{
			EnemyList.RemoveAt(i);
			return;
		}
	}
}

// �G�l�~�[�̑S����
void AEnemyManager::UnRegistAllEnemies()
{
	EnemyList.Empty();
}

// �G�l�~�[��1�l�ł������Ă��邩
bool AEnemyManager::IsAliveAnyEnemy()
{
	for (int i = EnemyList.Num() - 1; i >= 0; --i)
	{
		if (EnemyList[i]->IsDead() == false)
			return true;
	}

	return false;
}

// �S�G�l�~�[���J�n�\��Ԃ�
bool AEnemyManager::IsAllEnemyReady()
{
	for (int i = EnemyList.Num() - 1; i >= 0; --i)
	{
		if (EnemyList[i]->IsReady() == false)
			return false;
	}

	return true;
}

