// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HandCardsWidget.h"
#include "Components/HorizontalBoxSlot.h"
#include <Components/SizeBox.h>


// �J�[�h�I���f���Q�[�g��ݒ�
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

	// �f�[�^����E�B�W�F�b�g�𐶐����āA��D�z��ɒǉ�
	if (CardsWidgetClass)
	{
		UCardWidget* NewHandCard = CreateWidget<UCardWidget>(GetWorld(), CardsWidgetClass);
		if (NewHandCard)
		{
			// �J�[�h�̏����ݒ�
			NewHandCard->Initialize(CardData, SelectCardDelegate, UnSelectCardDelegate);

			// ��D�ɒǉ�
			HandCards.Add(NewHandCard);

			if (CardsHorizontalBox)
			{
				UHorizontalBoxSlot* BoxSlot = Cast<UHorizontalBoxSlot>(CardsHorizontalBox->AddChildToHorizontalBox(NewHandCard));
				if (BoxSlot)
				{
					// �J�[�h�Ԃ̗]����ǉ�
					BoxSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
					BoxSlot->SetVerticalAlignment(VAlign_Top);
				}
			}

			UE_LOG(LogTemp, Verbose, TEXT("Add to HandCards"));
		}
	}
}
