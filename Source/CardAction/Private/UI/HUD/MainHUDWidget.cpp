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
        // ゲームクリア
        if (GameClearWidgetClass)
        {
            GameClearWidget = CreateWidget<UUserWidget>(GetWorld(), GameClearWidgetClass);

            // キャンバスに追加
            if (MainCanvas)
            {
                MainCanvas->AddChild(GameClearWidget);
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

                    // 左下に配置
                    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HandCardsWidget->Slot);
                    if (CanvasSlot)
                    {
                        CanvasSlot->SetAnchors(FAnchors(0.f, 1.f));           // 左下
                        CanvasSlot->SetAlignment(FVector2D(0.f, 1.f));       // 左下基準
                        CanvasSlot->SetPosition(FVector2D(20.f, -20.f));     // 左下から50px右、50px上
                    }
                    HandCardsWidget->SetRenderScale(FVector2D(0.6f, 0.6f));
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
