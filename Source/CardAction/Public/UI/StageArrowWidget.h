// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageArrowWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageArrowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PlayHideAnim();
	void PlayIdleAnim();

private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* IdleAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HideAnim;
};
