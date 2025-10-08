// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardWidget.h"
#include <Components/TextBlock.h>
#include <Components/SizeBox.h>

void UCardWidget::NativeConstruct()
{
}

void UCardWidget::InitializeWidget(UCardData* Data)
{
    if (Data == nullptr)
        return;

    CardData = Data;

    // テキストの設定
    // 名前
    UTextBlock* NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
    if (NameText)
    {
        NameText->SetText(FText::FromName(CardData->Name));
    }
    // 説明
    UTextBlock* DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));
    if (DescText)
    {
        DescText->SetText(FText::FromString(CardData->Description));

        // 自動改行を有効化
        DescText->SetAutoWrapText(true);      
        USizeBox* SizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("TextBox")));
    }
}

void UCardWidget::Initialize(UCardData* Data, FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate)
{
    // ウィジェットの初期化
    InitializeWidget(Data);

    // デリゲートの設定
    SelectCardDelegate = SelectDelegate;
    UnSelectCardDelegate = UnSelectDelegate;
}

FReply UCardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        // 未選択の場合、選択中カードに追加
        if (bSelected == false)
        {
            if (SelectCardDelegate.IsBound())
            {
                SelectCardDelegate.Execute(CardData);

                // 選択中にする
                bSelected = true;

                // 選択中用のホバー画像を表示

            }
        }
        // 選択中の場合、選択中カードから外し再度選択可能にする
        else
        {
            UnSelectCardDelegate.Execute(CardData);

            // 未選択にする
            bSelected = false;

            // 選択中用のホバー画像を非表示
            
        }

        return FReply::Handled();
    }
    return FReply::Unhandled();
}

void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // 選択中のカードは選択できないよう示す
    if (bSelected)
        return;
 
    this->SetRenderScale(FVector2D(1.2f, 1.2f));
}

void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    this->SetRenderScale(FVector2D(1.f, 1.f));
}

// 効果発動
void UCardWidget::ExecuteEffect()
{
    if (CardData && CardData->Effect)
    {
        UCardEffectBase* Effect = NewObject<UCardEffectBase>(this, CardData->Effect);
        if (Effect)
        {
            Effect->ExecuteEffect();
        }
    }
}