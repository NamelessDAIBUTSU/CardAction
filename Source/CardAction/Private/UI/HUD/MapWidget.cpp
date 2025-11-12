// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MapWidget.h"
#include "Components/CanvasPanelSlot.h"
#include <Map/MapManager.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <UI/HUD/StageLineWidget.h>

void UMapWidget::OnUpdate(float DeltaSec)
{
	for (UStageWidget* StageWidget : StageWidgets)
	{
		StageWidget->OnUpdate(DeltaSec);
	}
}

void UMapWidget::SetupInfo(UMapData* Data)
{
	if (Data == nullptr)
		return;
	MapData = Data;

	if (GetWorld() == nullptr || GetWorld()->GetGameInstance() == nullptr)
		return;
	UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr || MapManager->GetCurrentMap() == nullptr)
		return;

	// マップ名を設定
	if (MapName)
	{
		MapName->SetText(FText::FromName(MapManager->GetCurrentMapName()));
	}
	// ヘッダー / フッター / ベース画像を設定
	if (HeaderImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->HeaderImage);
		HeaderImage->SetBrush(Brush);
	}
	if (FooterImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->FooterImage);
		FooterImage->SetBrush(Brush);
	}
	if (MapBaseImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->BaseImage);
		MapBaseImage->SetBrush(Brush);
	}

	// マップのサイズを取得
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

	// ステージウィジェットの位置
	FVector2D Position = FVector2D::Zero();
	Position.X = StartPosX + StagePos.X * StageDistX;
	Position.Y = StartPosY + StagePos.Y * StageDistY * -1.f;

	// ステージウィジェットの生成
	UStageWidget* NewStage = CreateWidget<UStageWidget>(GetWorld(), StageWidgetClass);
	if (NewStage == nullptr)
		return;
	StageWidgets.Add(NewStage);

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

void UMapWidget::CreateStageLineWidget()
{
	if (StageLineWidgetClass == nullptr)
		return;

	for (UStageWidget* StageWidget : StageWidgets)
	{
		UStageObject* Stage = StageWidget->GetStageObject();
		if (Stage == nullptr)
			continue;

		for (UStageObject* ChainedStage : Stage->GetChainedStageList())
		{
			if (ChainedStage == nullptr)
				continue;

			// 前ステージウィジェットの位置を取得
			FVector2D StagePos = FVector2D::Zero();
			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(StageWidget->Slot))
			{
				StagePos = CanvasSlot->GetPosition();
			}

			// ステージ間の幅を取得
			FVector2D DistPos = (ChainedStage->GetPos() - Stage->GetPos()) * 0.5f;

			// 前ステージの位置から幅分移動
			FVector2D LinePos = StagePos + FVector2D(StageDistX * DistPos.X, StageDistY * DistPos.Y * -1.f);

			// ステージラインウィジェットを生成
			UStageLineWidget* NewLine = CreateWidget<UStageLineWidget>(GetWorld(), StageLineWidgetClass);
			if (NewLine == nullptr)
				return;

			// 配置
			UCanvasPanelSlot* CanvasSlot = StageCanvas->AddChildToCanvas(NewLine);
			if (CanvasSlot)
			{
				// 自動サイズ調整
				CanvasSlot->SetAutoSize(true);
				// 左上座標で配置
				CanvasSlot->SetPosition(LinePos);
				// スロットの中心合わせ
				CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));

				// 三角形にしてcosΘを求めて角度計算
				// #MEMO : cosΘ = A^2 * B^2 / A・B
				FVector2D A = LinePos - StagePos;
				FVector2D B = FVector2D(1.f, 0.f);
				float AngleRad = FMath::Acos(
					FVector2D::DotProduct(A.GetSafeNormal(), B.GetSafeNormal())
				);
				float AngleDeg = FMath::RadiansToDegrees(AngleRad);
				// 上方向であれば角度を反転
				if (DistPos.Y > 0)
				{
					AngleDeg *= -1.f;
				}

				NewLine->SetRenderTransformAngle(AngleDeg);
			}

			// 後ろのステージを設定
			NewLine->SetPostStage(ChainedStage);

			// アニメーション設定
			NewLine->SetupAnim();
		}
	}
}
