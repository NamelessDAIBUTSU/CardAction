#include "System/Phase/BattlePhase_CardSelect.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include <Character/MyPlayerController.h>


// フェーズ開始時
void UBattlePhase_CardSelect::OnBegin() 
{ 
	// カード選択ウィジェットとカードブックの非表示
	SetHidden(false);
}

void UBattlePhase_CardSelect::OnTick(float DeltaSec)
{
	if (RequestNextPhase != EBattlePhase::None)
		return;

	// フェーズ切り替え判定
	// 時間でカード選択へ
	ElapsedSec += DeltaSec;
	if (ElapsedSec >= PhaseEndSec)
	{
		RequestNextPhase = EBattlePhase::Action;
		return;
	}
}

// フェーズ終了時
void UBattlePhase_CardSelect::OnExit() 
{
	// カード選択ウィジェットとカードブックの非表示
	SetHidden(true);
}

void UBattlePhase_CardSelect::SetHidden(bool bHidden)
{
	// カード選択ウィジェットの非表示
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
	if (CardSelectWidget == nullptr)
		return;

	ESlateVisibility Visibility = bHidden ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	CardSelectWidget->SetVisibility(Visibility);

	// アニメーション再生
	if (Visibility == ESlateVisibility::Visible)
	{
		CardSelectWidget->PlayAnimation(CardSelectWidget->InAnim);
	}
	if (Visibility == ESlateVisibility::Hidden)
	{
		CardSelectWidget->PlayAnimation(CardSelectWidget->OutAnim);
	}

	// カードブックの非表示
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
	{
		if (ACardBook* CardBook = MyGM->GetCardBook())
		{
			CardBook->SetActorHiddenInGame(bHidden);
		}
	}
}