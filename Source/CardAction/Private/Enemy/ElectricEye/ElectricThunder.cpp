// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ElectricEye/ElectricThunder.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"

AElectricThunder::AElectricThunder()
{
}

void AElectricThunder::BeginPlay()
{
	Super::BeginPlay();

	// エフェクトの再生
	FTimerHandle PlayEffectHandle;
	GetWorldTimerManager().SetTimer(PlayEffectHandle, this, &AElectricThunder::OnPlayEffect, 1.0f, false);

	// ダメージ処理を指定タイミングで行う
	FTimerHandle DamageTimerHandle;
	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &AElectricThunder::OnAttack, 1.3f, false);
}

void AElectricThunder::Tick(float DeltaSec)
{
	Super::Tick(DeltaSec);
}

// エフェクト終了時のコールバック
void AElectricThunder::OnPlayEffect()
{
	if (ThunderEffect)
	{
		UParticleSystemComponent* ParticleSysComp = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ThunderEffect,
			GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.f),
			true
		);
	}
}

// エフェクト終了時のコールバック
void AElectricThunder::OnAttack()
{
	if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		AGridManager* GridManager = MyGameMode->GridManager;
		if (GridManager == nullptr)
			return;

		// ダメージ処理
		GridManager->ExecuteAttackToCell(this, Damage, CurrentCoord);

		// 攻撃予測の削除
		GridManager->RemoveAttackSign(CurrentCoord);

		// 自身の削除
		Destroy();
	}
}
