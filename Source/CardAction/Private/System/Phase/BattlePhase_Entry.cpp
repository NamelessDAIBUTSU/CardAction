// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Entry.h"
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Enemy/EnemyManager.h"
#include <Card/DeckManager.h>

void UBattlePhase_Entry::OnBegin()
{
}

void UBattlePhase_Entry::OnTick(float DeltaSec)
{
	// 敵ステージじゃない場合はアクションフェーズへリクエスト
	if (false)
	{
		RequestNextPhase = EBattlePhase::Action;
		return;
	}

	// 全敵が開始準備を整えたらカード選択フェーズへリクエスト
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->EnemyManager && MyGM->EnemyManager->IsAllEnemyReady())
		{
			RequestNextPhase = EBattlePhase::CardSelect;
			return;
		}
	}
}
