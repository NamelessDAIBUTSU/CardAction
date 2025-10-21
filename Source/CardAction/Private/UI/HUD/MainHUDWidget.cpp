// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MainHUDWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBoxSlot.h"
#include <Components/WidgetComponent.h>

// 初期化
void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

    // 各Widgetの生成 & 配置
    // #MEMO : 初期化はゲームモードで他クラスが生成されてから行う
    CreateWidgets();
}

// 更新
void UMainHUDWidget::OnUpdate(float DeltaSec)
{
    for (UHUDBase* HUDWidget : HUDList)
    {
        if (HUDWidget == nullptr)
            continue;

        HUDWidget->OnUpdate(DeltaSec);
    }
}

// 各Widgetの生成 & 配置
void UMainHUDWidget::CreateWidgets()
{
    // ステージクリア
    if (StageClearWidgetClass)
    {
        StageClearWidget = CreateWidget<UStageClearWidget>(GetWorld(), StageClearWidgetClass);
        HUDList.Add(StageClearWidget);

        // 配置
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

    // 手札
    if (HandCardsWidgetClass)
    {
        HandCardsWidget = CreateWidget<UHandCardsWidget>(GetWorld(), HandCardsWidgetClass);
        HUDList.Add(HandCardsWidget);

        if (HandCardsWidget)
        {
            // デフォルト非表示
            HandCardsWidget->SetVisibility(ESlateVisibility::Hidden);

            // 選択時のデリゲート設定
            HandCardsWidget->SetSelectCardDelegate(SelectCardDelegate, UnSelectCardDelegate);

            // 配置
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

    // カード選択
    if (CardSelectWidgetClass)
    {
        CardSelectWidget = CreateWidget<UCardSelectWidget>(GetWorld(), CardSelectWidgetClass);
        HUDList.Add(CardSelectWidget);

        // 配置
        if (MainCanvas)
        {
            MainCanvas->AddChild(CardSelectWidget);
            UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(CardSelectWidget->Slot);
            if (CanvasSlot)
            {
                CanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
                CanvasSlot->SetOffsets(FMargin(0.f));
                CanvasSlot->SetZOrder(10);
            }
        }
    }

    // エネミーキャラバナー
    if (EnemyCharaBannerWidgetClass)
    {
        EnemyCharaBannerWidget = CreateWidget<UEnemyCharaBannerListWidget>(GetWorld(), EnemyCharaBannerWidgetClass);
        if (EnemyCharaBannerWidget)
        {
            HUDList.Add(EnemyCharaBannerWidget);

            // 配置
            if (EnemyCharaBannerBox)
            {
                EnemyCharaBannerBox->AddChild(EnemyCharaBannerWidget);
                USizeBoxSlot* SizeBoxSlot = Cast<USizeBoxSlot>(CardSelectWidget->Slot);
                if (SizeBoxSlot)
                {

                }
            }

            //if (MainCanvas)
            //{
            //    MainCanvas->AddChild(EnemyCharaBannerWidget);
            //    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(EnemyCharaBannerWidget->Slot);
            //    if (CanvasSlot)
            //    {
            //        CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
            //        CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
            //    }
            //}
        }
    }
}

// アクションフェーズ以外で表示にするUIの表示制御
void UMainHUDWidget::SetVisibleExceptActionPhase(bool Visible)
{
    for (UHUDBase* HUDWidget : HUDList)
    {
        if (HUDWidget == nullptr)
            continue;
        // アクションフェーズ以外でも表示するUIは、制御対象外
        if (HUDWidget->IsVisibleExceptActionPhase() == true)
            continue;

        if (Visible)
        {
            HUDWidget->SetVisibility(ESlateVisibility::Visible);
            HUDWidget->PlayInAnimation();
        }
        else
        {
            HUDWidget->PlayOutAnimation();
        }
    }

}

// 各Widgetの初期化
void UMainHUDWidget::InitializeWidgets()
{
    // カード選択
    if (CardSelectWidget)
    {
        // デフォルト非表示
        CardSelectWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    // エネミーキャラバナー
    if (EnemyCharaBannerWidget)
    {
        // バナーの初期化
        EnemyCharaBannerWidget->InitializeBanner();
    }
}
