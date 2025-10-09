// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HandCardsWidget.h"
#include "Components/HorizontalBoxSlot.h"
#include <Components/SizeBox.h>


// カード選択デリゲートを設定
void UHandCardsWidget::SetSelectCardDelegate(FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate) 
{
	SelectCardDelegate = SelectDelegate;
	UnSelectCardDelegate = UnSelectDelegate;
}

void UHandCardsWidget::AddToHandCards(UCardData* CardData)
{
	if (CardData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CardData is nullptr"));
		return;
	}

	if (HandCards.Num() >= MaxHandCardsNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("HandCards is Already Max(%d)"), MaxHandCardsNum);
		return;
	}

	// データからウィジェットを生成して、手札配列に追加
	if (CardsWidgetClass)
	{
		UCardWidget* NewHandCard = CreateWidget<UCardWidget>(GetWorld(), CardsWidgetClass);
		if (NewHandCard)
		{
			// カードの初期設定
			NewHandCard->Initialize(CardData, SelectCardDelegate, UnSelectCardDelegate);

			// 手札に追加
			HandCards.Add(NewHandCard);

			if (CardsHorizontalBox)
			{
				UHorizontalBoxSlot* BoxSlot = Cast<UHorizontalBoxSlot>(CardsHorizontalBox->AddChildToHorizontalBox(NewHandCard));
				if (BoxSlot)
				{
					// カード間の余白を追加
					BoxSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
					BoxSlot->SetVerticalAlignment(VAlign_Top);
				}
			}

			UE_LOG(LogTemp, Verbose, TEXT("Add to HandCards"));
		}
	}
}
