// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HandCardsWidget.h"
#include "Components/HorizontalBoxSlot.h"
#include <Components/SizeBox.h>


void UHandCardsWidget::NativeConstruct()
{
	// �J�[�h�z��̃T�C�Y�m��
	HandCards.Reserve(MAX_HAND_CARDS_NUM);

	if (CardSlotWidgetClass == nullptr)
		return;

	// �E�B�W�F�b�g�𐶐����āA��D�z��ɒǉ�
	for (auto i = 0; i < MAX_HAND_CARDS_NUM; i++)
	{
		UCardSlotWidget* NewCardSlot = CreateWidget<UCardSlotWidget>(GetWorld(), CardSlotWidgetClass);
		if (NewCardSlot)
		{
			HandCards.Add(NewCardSlot);
			if (CardsHorizontalBox)
			{
				UHorizontalBoxSlot* BoxSlot = Cast<UHorizontalBoxSlot>(CardsHorizontalBox->AddChildToHorizontalBox(NewCardSlot));
				if (BoxSlot)
				{
					// �J�[�h�Ԃ̗]����ǉ�
					BoxSlot->SetPadding(FMargin(5.f, 0.f, 5.f, 0.f));
					BoxSlot->SetVerticalAlignment(VAlign_Bottom);
				}
			}
		}
	}
}

// �J�[�h�I���f���Q�[�g��ݒ�
void UHandCardsWidget::SetSelectCardDelegate(FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate) 
{
	SelectCardDelegate = SelectDelegate;
	UnSelectCardDelegate = UnSelectDelegate;
}

void UHandCardsWidget::AddToHandCards(int Index, UCardData* CardData)
{
	if (Index >= MAX_HAND_CARDS_NUM)
		return;

	if (HandCards[Index])
	{
		HandCards[Index]->SetupCardSlot(CardData);
	}
}

// ��D�J�[�h�����Z�b�g
void UHandCardsWidget::ResetHandCards()
{
	for (int i = 0; i < HandCards.Num(); ++i)
	{
		ResetHandCards(i);
	}
}
void UHandCardsWidget::ResetHandCards(int Index)
{
	if (HandCards.Num() <= Index)
		return;

	if (HandCards[Index])
	{
		HandCards[Index]->SetupCardSlot(nullptr);
	}
}

// �J�[�h�I��
void UHandCardsWidget::SelectCard(int SelectIndex)
{
	if (SelectIndex >= MAX_HAND_CARDS_NUM)
		return;

	if (HandCards[SelectIndex] == nullptr)
		return;

	// �I���A�j���[�V����
	HandCards[SelectIndex]->PlaySelectAnim();

	// �I�𒆂̃J�[�h������ΑI�������A�j���[�V�����̍Đ�
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

// �J�[�h�̌��ʔ���
void UHandCardsWidget::ExecuteEffect(int Index)
{
	if (Index >= MAX_HAND_CARDS_NUM)
		return;

	if (HandCards[Index] == nullptr)
		return;

	// ���ʔ���
	HandCards[Index]->ExecuteEffect();
}
