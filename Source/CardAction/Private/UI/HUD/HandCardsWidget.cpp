// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HandCardsWidget.h"
#include "Components/HorizontalBoxSlot.h"
#include <Components/SizeBox.h>


void UHandCardsWidget::NativeConstruct()
{
	// カード配列のサイズ確保
	HandCards.Reserve(MAX_HAND_CARDS_NUM);

	if (CardSlotWidgetClass == nullptr)
		return;

	// ウィジェットを生成して、手札配列に追加
	for (auto i = 0; i < MAX_HAND_CARDS_NUM; i++)
	{
		UCardSlotWidget* NewCardSlot = CreateWidget<UCardSlotWidget>(GetWorld(), CardSlotWidgetClass);
		if (NewCardSlot)
		{
			// スロット番号設定
			NewCardSlot->SetupSlotNum(i);

			HandCards.Add(NewCardSlot);
			if (CardsHorizontalBox)
			{
				UHorizontalBoxSlot* BoxSlot = Cast<UHorizontalBoxSlot>(CardsHorizontalBox->AddChildToHorizontalBox(NewCardSlot));
				if (BoxSlot)
				{
					// カード間の余白を追加
					BoxSlot->SetPadding(FMargin(10.f, 0.f, 10.f, 0.f));
					BoxSlot->SetVerticalAlignment(VAlign_Bottom);
				}
			}
		}
	}
}

// カード選択デリゲートを設定
void UHandCardsWidget::SetSelectCardDelegate(FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate) 
{
	SelectCardDelegate = SelectDelegate;
	UnSelectCardDelegate = UnSelectDelegate;
}

void UHandCardsWidget::AddToHandCards(int Index, UCardData* CardData)
{
	if (CardData == nullptr)
		return;

	if (Index >= MAX_HAND_CARDS_NUM)
		return;

	if (HandCards[Index])
	{
		HandCards[Index]->SetupCardSlot(CardData);
	}
}

// カード選択
void UHandCardsWidget::SelectCard(int SelectIndex)
{
	if (SelectIndex >= MAX_HAND_CARDS_NUM)
		return;

	if (HandCards[SelectIndex] == nullptr)
		return;

	// 選択アニメーション
	HandCards[SelectIndex]->PlaySelectAnim();

	// 選択中のカードがあれば選択解除アニメーションの再生
	for (auto i = 0; i < MAX_HAND_CARDS_NUM; i++)
	{
		if (i == SelectIndex)
			continue;

		if (HandCards[i] && HandCards[i]->bIsSelected)
		{
			HandCards[i]->PlayUnSelectAnim();
		}
	}
}

// カードの効果発動
void UHandCardsWidget::ExecuteEffect(int Index)
{
	if (Index >= MAX_HAND_CARDS_NUM)
		return;

	if (HandCards[Index] == nullptr)
		return;

	// 効果発動
	HandCards[Index]->ExecuteEffect();
}
