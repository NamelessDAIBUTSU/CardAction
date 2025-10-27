// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Map/Stage/StageObject.h>
#include "StageLineWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageLineWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 後のステージを設定
	void SetPostStage(UStageObject* Post);

	// アニメーション設定
	void SetupAnim();

private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* StageLineAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PointLineAnim;

	// 後のステージ
	UStageObject* PostStage = nullptr;
};
