// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MapWidget.h"
#include "Components/CanvasPanelSlot.h"
#include <Map/MapManager.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UMapWidget::SetupInfo()
{
	// マップのサイズを取得
	if (GetWorld() == nullptr || GetWorld()->GetGameInstance() == nullptr)
		return;
	UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr || MapManager->GetCurrentMap() == nullptr)
		return;
	FVector2D MapSize = MapManager->GetCurrentMap()->GetSize();

	// 解像度取得
	float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
	FVector2D ViewportSize;
	if (UGameViewportClient* Viewport = GetWorld()->GetGameViewport())
	{
		Viewport->GetViewportSize(ViewportSize);
	}
	// DPIスケールを考慮して、補正済み論理値に変換
	ViewportSize /= Scale;

	// ステージ間距離を算出
	StageDistX = (ViewportSize.X - OffsetX * 2.f) / MapSize.X;
	StageDistY = (ViewportSize.Y - OffsetY * 2.f) / MapSize.Y;

	// 初期ステージのX座標
	StartPosX = OffsetX + StageDistX * 0.5f;
	// 初期ステージのY座標
	StartPosY = OffsetY + StageDistY * MapSize.Y * 0.5f;
}

// キャンバスにステージを追加
void UMapWidget::CreateStageWidget(UStageObject* Stage)
{
	if (StageCanvas == nullptr)
		return;
	if (StageWidgetClass == nullptr || Stage == nullptr)
		return;

	FVector2D StagePos = Stage->GetPos();

	FVector2D Position = FVector2D::Zero();
	// 水平方向：開始位置からWidth分だけステージ間距離をずらした位置
	Position.X = StartPosX + StagePos.X * StageDistX;
	// 垂直方向：
	Position.Y = StartPosY + StagePos.Y * StageDistY;

	// ステージウィジェットの生成
	UStageWidget* NewStage = CreateWidget<UStageWidget>(GetWorld(), StageWidgetClass);
	if (NewStage == nullptr)
		return;

	// ステージ情報の設定
	NewStage->SetStageObject(Stage);

	// 配置設定
	UCanvasPanelSlot* CanvasSlot = StageCanvas->AddChildToCanvas(NewStage);
	if (CanvasSlot)
	{
		// 自動サイズ調整
		CanvasSlot->SetAutoSize(true);                 
		// 左上座標で配置
		CanvasSlot->SetPosition(Position);
		// スロットの中心合わせ
		CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	}

	// ステージ状況に合わせたアニメーション再生
	NewStage->PlayConditionAnim();
}
