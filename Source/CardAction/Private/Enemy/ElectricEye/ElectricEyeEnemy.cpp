// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ElectricEye/ElectricEyeEnemy.h"

AElectricEyeEnemy::AElectricEyeEnemy()
{
}

void AElectricEyeEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 指定時間後に開始準備フラグを立てる
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AElectricEyeEnemy::OnSetReady, StartReadySec, true);
}

void AElectricEyeEnemy::OnSetReady()
{
	bCanCardSelect = true; 
}
