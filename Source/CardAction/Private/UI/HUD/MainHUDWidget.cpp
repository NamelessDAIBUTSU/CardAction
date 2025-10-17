// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MainHUDWidget.h"
#include "Components/CanvasPanelSlot.h"
#include <Components/WidgetComponent.h>

// 初期化
void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

    SelectCardDelegate.BindUObject(this, &UMainHUDWidget::OnAddToSelectedCards);
    UnSelectCardDelegate.BindUObject(this, &UMainHUDWidget::OnRemoveFromSelectedCards);

    // ウィジェットの生成
    {
        // ステージクリア
        if (StageClearWidgetClass)
        {
            StageClearWidget = CreateWidget<UStageClearWidget>(GetWorld(), StageClearWidgetClass);

            // キャンバスに追加
            if (MainCanvas)
            {
                MainCanvas->AddChild(StageClearWidget);

                // 中央に配置
                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(StageClearWidget->Slot);
                if (CanvasSlot)
                {
                    CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
                    CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
                }
            }
        }

        // ゲームオーバー
        if (GameOverWidgetClass)
        {
            GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);

            // キャンバスに追加
            if (MainCanvas)
            {
                MainCanvas->AddChild(GameOverWidget);
                // デフォルト非表示
                GameOverWidget->SetVisibility(ESlateVisibility::Hidden);
            }
        }

        // HPゲージ
        if (HPGaugeWidgetClass)
        {
            UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), HPGaugeWidgetClass);
            HPGaugeWidget = Cast<UHPGauge>(widget);

            // キャンバスに追加
            if (MainCanvas)
            {
                MainCanvas->AddChild(HPGaugeWidget);
            }
        }

        // 手札
        if (HandCardsWidgetClass)
        {
            HandCardsWidget = CreateWidget<UHandCardsWidget>(GetWorld(), HandCardsWidgetClass);
            if (HandCardsWidget)
            {
                HandCardsWidget->SetSelectCardDelegate(SelectCardDelegate, UnSelectCardDelegate);

                // キャンバスに追加
                if (MainCanvas)
                {
                    MainCanvas->AddChild(HandCardsWidget);

                    // 真ん中下に配置
                    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HandCardsWidget->Slot);
                    if (CanvasSlot)
                    {
                        CanvasSlot->SetAnchors(FAnchors(0.5f, 1.f));
                        CanvasSlot->SetAlignment(FVector2D(0.5f, 1.f));

                        // 中央に配置（オフセットは任意）
                        CanvasSlot->SetPosition(FVector2D(0.0f, -15.0f));
                        // 中身のサイズに合わせる
                        CanvasSlot->SetAutoSize(true);
                    }
                }
            }
        }

        // 選択中カード
        if (SelectedCardsWidgetClass)
        {
            SelectedCardsWidget = CreateWidget<USelectedCardsWidget>(GetWorld(), SelectedCardsWidgetClass);
            // キャンバスに追加
            if (MainCanvas)
            {
                MainCanvas->AddChild(SelectedCardsWidget);

                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SelectedCardsWidget->Slot);
                if (CanvasSlot)
                {
                    // 真ん中下
                    CanvasSlot->SetAnchors(FAnchors(0.5f, 1.f));
                    CanvasSlot->SetAlignment(FVector2D(0.5f, 1.f));
                }
                //SelectedCardsWidget->SetRenderScale(FVector2D(0.75f, 0.75f));
            }
        }

        // カード選択
        if (CardSelectWidgetClass)
        {
            CardSelectWidget = CreateWidget<UCardSelectWidget>(GetWorld(), CardSelectWidgetClass);
            if (MainCanvas)
            {
                MainCanvas->AddChild(CardSelectWidget);
                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(CardSelectWidget->Slot);
                if (CanvasSlot)
                {
                    CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
                    CanvasSlot->SetOffsets(FMargin(0.f));
                }
            }

            // デフォルト非表示
            CardSelectWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

}

// 更新
void UMainHUDWidget::OnTick(float InDeltaTime)
{
    if (HPGaugeWidget)
    {
        HPGaugeWidget->OnUpdateHPGauge();
    }
}

// 選択中カードに追加
void UMainHUDWidget::OnAddToSelectedCards(UCardData* CardData)
{
    if (SelectedCardsWidget)
    {
        SelectedCardsWidget->AddToSelectedCards(CardData);
    }
}

void UMainHUDWidget::OnRemoveFromSelectedCards(UCardData* CardData)
{
    if (SelectedCardsWidget)
    {
        SelectedCardsWidget->RemoveFromSelectedCards(CardData);
    }
}
