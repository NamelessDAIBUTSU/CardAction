// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Action.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include <Grid/GridManager.h>
#include <Character/MyPlayerController.h>


// フェーズ開始時
void UBattlePhase_Action::OnBegin() 
{ 
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;

	// アクションフェーズ以外で非表示にするウィジェットを表示
	PlayerController->MainHUDWidget->SetVisibleExceptActionPhase(true);
}

// フェーズ中
void UBattlePhase_Action::OnTick(float DeltaSec)
{
	if (RequestNextPhase != EBattlePhase::None)
		return;

	// フェーズ切り替え判定
	// 時間でカード選択へ
	ElapsedSec += DeltaSec;
	if (ElapsedSec >= PhaseEndSec)
	{
		RequestNextPhase = EBattlePhase::CardSelect;
		return;
	}

	// 敵殲滅でリザルトへ
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
			return;
		}
	}
}

void UBattlePhase_Action::OnExit()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;

	// アクションフェーズ以外で非表示にするウィジェットを消す
	PlayerController->MainHUDWidget->SetVisibleExceptActionPhase(false);
}

// 残り時間を整数で取得
int UBattlePhase_Action::GetCurrentRemainSec()
{
	float RemainSec = PhaseEndSec - ElapsedSec;

	return FMath::FloorToInt(RemainSec);
}
