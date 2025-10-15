// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardWidget.h"
#include <Components/TextBlock.h>
#include <Components/SizeBox.h>

void UCardWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (CardButton)
    {
        CardButton->OnClicked.AddDynamic(this, &UCardWidget::OnCardClicked);
    }
}

void UCardWidget::SetupCardData(UCardData* Data)
{
    CardData = Data;

    if (CardData == nullptr)
        return;

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

void UCardWidget::Initialize(UCardData* Data, const FCardWidgetOption& WidgetOption)
{
    // ウィジェットの初期化
    SetupCardData(Data);

    // 表示オプションの設定
    Option = WidgetOption;
}

// クリック時
void UCardWidget::OnCardClicked()
{
    if (Option.bCanMouseOver == false)
        return;

    // 選択
    if (bSelected == false)
    {
        if (Option.SelectCardDelegate.IsBound())
        {
            Option.SelectCardDelegate.Execute(CardData);

            // 選択中にする
            bSelected = true;

            // 選択中用のホバー画像を表示
            if (SelectAnim)
            {
                PlayAnimation(SelectAnim);
            }
        }
    }
    // 選択解除
    else
    {
        Option.UnSelectCardDelegate.Execute(CardData);

        // 未選択にする
        bSelected = false;

        // 選択中用のホバー画像を非表示
        if (UnSelectAnim)
        {
            PlayAnimation(UnSelectAnim);
        }
    }
}

// マウスオーバー時
void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("Over"));

    if (Option.bCanMouseOver == false)
        return;

    // スケール変更
    if (Option.bChangeScale && MouseOverAnim)
    {
        StopAnimation(MouseReleaseAnim);
        PlayAnimation(MouseOverAnim);
    }

    // ツールチップ表示
    if (Option.bShowToolTip)
    {

    }
}

// マウスオーバーから離れた時
void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("Leave"));

    if (Option.bCanMouseOver == false)
        return;

    // スケール変更
    if (Option.bChangeScale && MouseReleaseAnim)
    {
        StopAnimation(MouseOverAnim);
        PlayAnimation(MouseReleaseAnim);
    }

    // ツールチップ非表示
    if (Option.bShowToolTip)
    {

    }
}

// 効果発動
void UCardWidget::ExecuteEffect()
{
    if (IsValid(this) == false)
    {
        UE_LOG(LogTemp, Error, TEXT("this is not valid"));
        return;
    }

    if (CardData && CardData->EffectClass)
    {
        UCardEffectBase* Effect = NewObject<UCardEffectBase>(this, CardData->EffectClass);
        if (Effect)
        {
            Effect->ExecuteEffect();
        }
    }
}