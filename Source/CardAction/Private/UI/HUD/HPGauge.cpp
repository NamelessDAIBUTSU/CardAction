// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HPGauge.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

void UHPGauge::NativeConstruct()
{
	// 更新に使うオブジェクトを取得しておく
	{
		if (ProgressBar == nullptr)
		{
			ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
		}
		if (TextBlock == nullptr)
		{
			TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
		}
		if (Player == nullptr)
		{
			if (APlayerController* PlayerController = GetOwningPlayer())
			{
				Player = Cast<AMyCharacter>(PlayerController->GetPawn());
			}
		}

	}

	if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
	{
		if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
		{
			MyGameMode->OnGameEnd.AddLambda([this]() {

				});
		}
	}
}

void UHPGauge::OnUpdateHPGauge()
{
	if (ProgressBar == nullptr || Player == nullptr)
	{
		if (APlayerController* PlayerController = GetOwningPlayer())
		{
			Player = Cast<AMyCharacter>(PlayerController->GetPawn());
		}
		return;
	}

	// 0除算回避
	if (Player->MaxHP == 0)
		return;

	// ゲージ更新
	float Rate = Player->CurrentHP / (float)Player->MaxHP;
	ProgressBar->SetPercent(Rate);

	// テキスト更新
	FFormatNamedArguments Args;
	Args.Add(TEXT("CurrentHP"), Player->CurrentHP);
	Args.Add(TEXT("MaxHP"), Player->MaxHP);
	TextBlock->SetText(FText::Format(FTextFormat::FromString("{CurrentHP} / {MaxHP}"), Args));
}
