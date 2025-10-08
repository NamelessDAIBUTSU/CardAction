// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Character/MyCharacter.h>
#include "HPGauge.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UHPGauge : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void OnUpdateHPGauge();

private:
	UProgressBar* ProgressBar = nullptr;
	UTextBlock* TextBlock = nullptr;
	AMyCharacter* Player = nullptr;
};
