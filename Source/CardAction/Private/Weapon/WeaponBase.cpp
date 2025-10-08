// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

AWeaponActorBase::AWeaponActorBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;
}

AWeaponActorBase::~AWeaponActorBase()
{
}
