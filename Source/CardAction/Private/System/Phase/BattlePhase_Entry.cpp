// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Entry.h"
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Enemy/EnemyManager.h"

void UBattlePhase_Entry::OnTick(float DeltaSec)
{
	// 敵ステージじゃない場合はすぐにアクションフェーズへリクエスト
	if (false)
	{
		RequestNextPhase = EBattlePhase::Action;
		return;
	}

	// グリッド上にいる全敵がエントリーモーションを行ったらカード選択フェーズへリクエスト
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->EnemyManager && MyGM->EnemyManager->IsAllEnemyReady())
		{
			RequestNextPhase = EBattlePhase::CardSelect;
			return;
		}
	}
}
