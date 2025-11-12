// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

AWeaponActorBase::AWeaponActorBase()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (MeshComp)
	{
		MeshComp->SetupAttachment(RootComponent);
	}
}

AWeaponActorBase::~AWeaponActorBase()
{
}
