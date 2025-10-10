// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAttackBase.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

AEnemyAttackBase::AEnemyAttackBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// ���b�V��
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	if (MeshComp)
	{
		MeshComp->SetupAttachment(RootComponent);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AEnemyAttackBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyAttackBase::Tick(float DeltaTime)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// �A�N�V�����t�F�[�Y�ȊO�ł͎��Ԓ�~
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
	{
		this->CustomTimeDilation = 0.f;
		return;
	}

	this->CustomTimeDilation = 1.f;

	Super::Tick(DeltaTime);
}

