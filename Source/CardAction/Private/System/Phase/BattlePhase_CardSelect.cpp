#include "System/Phase/BattlePhase_CardSelect.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include <Character/MyPlayerController.h>


// フェーズ開始時
void UBattlePhase_CardSelect::OnBegin()
{
	// カード選択ウィジェットとカードブックの表示
	SetHidden(false);

	// 表示アニメーション
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
	if (CardSelectWidget == nullptr)
		return;

	CardSelectWidget->PlayInAnimation();
}

void UBattlePhase_CardSelect::OnTick(float DeltaSec)
{
	if (RequestNextPhase != EBattlePhase::None)
		return;

	// フェーズ切り替え判定
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
	if (CardSelectWidget == nullptr)
		return;

	// 決定ボタンが押されたら、終了アニメーションを待ってからアクションフェーズへリクエスト
	if (CardSelectWidget->GetIsDecided())
	{
		RequestNextPhase = EBattlePhase::Action;
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