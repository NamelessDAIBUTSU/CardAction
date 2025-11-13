// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/CanvasPanel.h>
#include "StageWidget.h"
#include "Map/Stage/StageObject.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Map/MapData.h>
#include "MapWidget.generated.h"

/// <summary>
/// ウィジェット：マップウィジェット。ステージウィジェットを管理
/// </summary>
UCLASS()
class CARDACTION_API UMapWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// 各種変数設定
	void SetupInfo(UMapData* Data);

	// キャンバスにステージを追加
	void CreateStageWidget(UStageObject* Stage);

	// キャンバスにステージ線を追加
	void CreateStageLineWidget();

	// エンジンから独立した更新クラス
	virtual void OnUpdate(float DeltaSec) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> StageWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> StageLineWidgetClass;

	// 配置オフセット
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetX = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetY = 150.f;

private: /* ウィジェット */
	// ほかウィジェット追加用キャンバス
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* StageCanvas = nullptr;

	// マップ名テキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MapName = nullptr;

	// ヘッダー / フッカー / 背景
	UPROPERTY(meta = (BindWidget))
	UImage* HeaderImage = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* FooterImage = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* MapBaseImage = nullptr;

private:
	// マップデータ
	UPROPERTY()
	UMapData* MapData = nullptr;

	// ステージウィジェット
	UPROPERTY()
	TArray<UStageWidget*> StageWidgets;
	
	// ステージ間の距離
	UPROPERTY()
	float StageDistX = 0.f;
	UPROPERTY()
	float StageDistY = 0.f;
	// 初期ステージの座標
	UPROPERTY()
	float StartPosX = 0.f;
	UPROPERTY()
	float StartPosY = 0.f;
};
