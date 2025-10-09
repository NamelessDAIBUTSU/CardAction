// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Action.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

// フェーズ中
void UBattlePhase_Action::OnTick(float DeltaSec)
{
	// フェーズ切り替え判定
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
	{
		AGridManager* GridManager = MyGameMode->GridManager;
		if (GridManager == nullptr)
			return;

		// 敵が全滅していたら、リザルトフェーズへの切り替えリクエスト
		if (GridManager->IsExistEnemyOnGrid() == false)
		{
			RequestNextPhase = EBattlePhase::Result;
		}
	}
}
