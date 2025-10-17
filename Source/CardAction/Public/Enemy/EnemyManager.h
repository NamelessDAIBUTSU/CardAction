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
	// �G�l�~�[�̓o�^ / ����
	void RegistEnemy(AEnemyBase* Enemy);
	void UnRegistEnemy(AEnemyBase* Enemy);

	// �S�G�l�~�[�̉���
	void UnRegistAllEnemies();

	// �G�l�~�[��1�l�ł������Ă��邩
	bool IsAliveAnyEnemy();

	// �S�G�l�~�[���J�n�\��Ԃ�
	bool IsAllEnemyReady();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<AEnemyBase*> Enemies;
};
