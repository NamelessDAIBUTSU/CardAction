// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ActionTimeWidget.h"
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>

void UActionTimeWidget::OnUpdate(float DeltaSec)
{
	if (RemainTimeText == nullptr)
		return;

	if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("Time"), MyGameMode->GetRemainSec());
		RemainTimeText->SetText(FText::Format(FTextFormat::FromString("{Time}"), Args));
	}
}
