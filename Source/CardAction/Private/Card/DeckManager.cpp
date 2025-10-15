// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/DeckManager.h"

void ADeckManager::Initialzie(UInitDeckData* InitDeckData)
{
	if (InitDeckData == nullptr)
		return;

	for (UCardData* CardData : InitDeckData->Cards)
	{
		AddToDeck(CardData);
	}
}

// �J�[�h�̒ǉ�
void ADeckManager::AddToDeck(UCardData* NewCard)
{
	Deck.Add(NewCard);
}

// �J�[�h�̏���
void ADeckManager::RemoveFromDeck(UCardData* RemoveCard)
{
	Deck.Remove(RemoveCard);
}

// �J�[�h������
TArray<UCardData*> ADeckManager::DrawCards()
{
	TArray<UCardData*> DrawCards;
	DrawCards.Reserve(DRAW_CARDS_NUM);

	for (int i = 0; i < DRAW_CARDS_NUM; ++i)
	{
		// �f�b�L�Ō�܂ł�����A�V���b�t�����čēx��������
		if (DrawIndex == ShuffledDeck.Num())
		{
			DrawIndex = 0;

			CreateShuffledDeck();
		}

		if (ShuffledDeck.IsEmpty())
			break;

		DrawCards.Add(ShuffledDeck[DrawIndex]);

		DrawIndex++;
	}

	return DrawCards;
}

// �V���b�t�����ꂽ�f�b�L���쐬
void ADeckManager::CreateShuffledDeck()
{
	ShuffledDeck = Deck;

	ShuffleArray(ShuffledDeck);
}

// �V���b�t��
void ADeckManager::ShuffleArray(TArray<UCardData*>& Array)
{
	for (int32 i = Array.Num() - 1; i > 0; --i)
	{
		int32 j = FMath::RandRange(0, i);
		Array.Swap(i, j);
	}
}