// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Action.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

// フェーズ中
void UBattlePhase_Action::OnTick(float DeltaSec)
{
	// 敵が全滅していたらフェーズを切り替えフラグを立てる
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
	{
		AGridManager* GridManager = MyGameMode->GridManager;
		if (GridManager == nullptr)
			return;

		bRequestChangePhase = (GridManager->IsExistEnemyOnGrid() == false);
	}
}
