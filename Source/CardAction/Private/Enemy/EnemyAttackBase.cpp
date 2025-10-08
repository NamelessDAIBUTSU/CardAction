// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAttackBase.h"

AEnemyAttackBase::AEnemyAttackBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// ÉÅÉbÉVÉÖ
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
	Super::Tick(DeltaTime);

}

