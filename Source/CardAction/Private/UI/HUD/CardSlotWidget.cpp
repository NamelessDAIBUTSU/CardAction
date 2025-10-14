// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSlotWidget.h"
#include <Card/CardData.h>
#include <UI/HUD/CardWidget.h>
#include <Components/SizeBoxSlot.h>

// スロット番号の設定
void UCardSlotWidget::SetupSlotNum(int Num)
{
	if (SlotNum == nullptr)
		return;

	FFormatNamedArguments Args;
	Args.Add(TEXT("Num"), Num);
	SlotNum->SetText(FText::Format(FTextFormat::FromString("{Num}"), Args));
}

// スロットにカードを設定
void UCardSlotWidget::SetupCardSlot(UCardData* Data)
{
	// カードウィジェットの生成
	if (CardWidgetClass)
	{
		CardWidget = CreateWidget<UCardWidget>(GetWorld(), CardWidgetClass);
		if (CardWidget)
		{
			CardWidget->InitializeWidget(Data);
		}

		// カードをボックスに配置
		if (CardBox)
		{
			USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardBox->AddChild(CardWidget));
		}
	}
}

// カード選択アニメーション再生
void UCardSlotWidget::PlaySelectAnim()
{
	if (SelectAnim)
	{
		PlayAnimation(SelectAnim);
		bIsSelected = true;
	}
}
// カード選択解除アニメーション再生
void UCardSlotWidget::PlayUnSelectAnim()
{
	if (UnSelectAnim)
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