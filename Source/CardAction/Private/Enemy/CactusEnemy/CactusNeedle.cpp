// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CactusEnemy/CactusNeedle.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"

void ACactusNeedle::BeginPlay()
{
	Super::BeginPlay();

	// スケールスピード
	ScaleSpeed = GoalScale / GoalSec;
}

void ACactusNeedle::Setup()
{
	if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGameMode->GridManager)
		{
			// 座標を設定
			CurrentCoord = MyGameMode->GridManager->ConvertToGridCoord(GetActorLocation());

			// 攻撃予兆を追加
			MyGameMode->GridManager->AddAttackSign(CurrentCoord);
		}
	}
}

void ACactusNeedle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedSec += DeltaTime;

	// 回転演出
	FRotator Rotation = GetActorRotation();
	Rotation.Yaw += RotateSpeed * DeltaTime;
	SetActorRotation(Rotation);

	// スケール演出
	if (MeshComp)
	{
		FVector CurrentScale = MeshComp->GetComponentScale();
		CurrentScale += ScaleSpeed * DeltaTime;
		MeshComp->SetWorldScale3D(CurrentScale);
	}

	if (ElapsedSec >= GoalSec)
	{
		if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			if (MyGameMode->GridManager)
			{
				// ダメージ判定を追加
				MyGameMode->GridManager->ExecuteAttackToGridCell(this, Damage, CurrentCoord);

				// 攻撃予兆を削除
				MyGameMode->GridManager->RemoveAttackSign(CurrentCoord);
			}
		}

		// エフェクトの再生


		// 自身の削除
		Destroy();
	}
}

