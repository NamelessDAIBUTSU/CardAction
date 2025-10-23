// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/CanvasPanel.h>
#include "StageWidget.h"
#include "Map/Stage/StageObject.h"
#include "MapWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMapWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// ステージ追加するための各種変数設定
	void SetupInfo();

	// キャンバスにステージを追加
	void CreateStageWidget(UStageObject* Stage);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> StageWidgetClass;

	// 配置オフセット
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetX = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetY = 150.f;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* StageCanvas = nullptr;

	// ステージ間の距離
	float StageDistX = 0.f;
	float StageDistY = 0.f;
	// 初期ステージの座標
	float StartPosX = 0.f;
	float StartPosY = 0.f;
};
