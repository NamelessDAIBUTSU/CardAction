// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Result.h"
#include <Character/MyPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "UI/HUD/StageClearWidget.h"
#include <System/FadeSystem.h>


// フェーズ開始時
void UBattlePhase_Result::OnBegin()
{
	// ステージクリアウィジェットの表示とアニメーション
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UStageClearWidget* StageClearWidget = PlayerController->MainHUDWidget->StageClearWidget;
	if (StageClearWidget == nullptr)
		return;

	StageClearWidget->SetVisibility(ESlateVisibility::Visible);
	StageClearWidget->PlayInAnim();
}

void UBattlePhase_Result::OnTick(float DeltaSec)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UStageClearWidget* StageClearWidget = PlayerController->MainHUDWidget->StageClearWidget;
	if (StageClearWidget == nullptr)
		return;

	// ステージクリアウィジェットのOutAnimが終了したらステージ選択レベルに移動する
	if (StageClearWidget->IsOutAnimFinished())
	{
		RequestNextPhase = EBattlePhase::End;
	}
}

// フェードアウトしてステージ選択レベルに遷移
void UBattlePhase_Result::OnExit()
{
	if (GetWorld()->GetGameInstance() == nullptr)
		return;

	UFadeSystem* FadeSystem = GetWorld()->GetGameInstance()->GetSubsystem<UFadeSystem>();
	if (FadeSystem == nullptr)
		return;

	FadeSystem->FadeOutAndOpenLevel(FName("SelectStageLevel"));
}
