// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSlotWidget.h"
#include <Card/CardData.h>
#include <UI/HUD/CardWidget.h>
#include <Components/SizeBoxSlot.h>

void UCardSlotWidget::NativeConstruct()
{
	// カードウィジェットの生成
	if (CardWidgetClass)
	{
		CardWidget = CreateWidget<UCardWidget>(GetWorld(), CardWidgetClass);
		if (CardWidget)
		{
			// 初期化
			FCardWidgetOption Option;
			// スケールアップなし
			Option.bChangeScale = false;
			CardWidget->Initialize(nullptr, Option);

			// 初期非表示
			CardWidget->SetVisibility(ESlateVisibility::Hidden);

			// カードをボックスに配置
			if (CardBox)
			{
				if (USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardBox->AddChild(CardWidget)))
				{

				}
			}
		}
	}
}

// スロットにカード情報を設定
void UCardSlotWidget::SetupCardSlot(UCardData* Data)
{
	if (CardWidget)
	{
		// カードデータを渡す
		CardWidget->SetupCardData(Data);

		// 表示設定
		if (Data == nullptr)
		{
			CardWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			CardWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

// カード選択アニメーション再生
void UCardSlotWidget::PlaySelectAnim()
{
	if (bIsSelected == false && SelectAnim)
	{
		PlayAnimation(SelectAnim);
		bIsSelected = true;
	}
}
// カード選択解除アニメーション再生
void UCardSlotWidget::PlayUnSelectAnim()
{
	if (bIsSelected && UnSelectAnim)
	{
		PlayAnimation(UnSelectAnim);
		bIsSelected = false;
	}
}

// 効果発動
void UCardSlotWidget::ExecuteEffect()
{
	if (CardWidget)
	{
		CardWidget->ExecuteEffect();
	}
}

// カードウィジェットのアニメーションをデフォルトに戻す
void UCardSlotWidget::PlayDefaultAnimation()
{
	if (CardWidget)
	{
		CardWidget->PlayDefaultAnimation();
	}
}