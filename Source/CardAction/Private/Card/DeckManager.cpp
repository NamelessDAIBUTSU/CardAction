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

// カードの追加
void ADeckManager::AddToDeck(UCardData* NewCard)
{
	if (NewCard == nullptr)
		return;

	// DataAssetを複製して独立したインスタンスにする
	UCardData* Instance = DuplicateObject<UCardData>(NewCard, GetTransientPackage());

	// ユニークIDの生成
	Instance->UniqueID = FName(*FGuid::NewGuid().ToString());
	Deck.Add(Instance);
}

// カードの除去
void ADeckManager::RemoveFromDeck(UCardData* RemoveCard)
{
	Deck.Remove(RemoveCard);
}

// カードを引く
TArray<UCardData*> ADeckManager::DrawCards()
{
	TArray<UCardData*> DrawCards;
	DrawCards.Reserve(DRAW_CARDS_NUM);

	for (int i = 0; i < DRAW_CARDS_NUM; ++i)
	{
		// デッキ最後まできたら、シャッフルして再度引き直す
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

// シャッフルされたデッキを作成
void ADeckManager::CreateShuffledDeck()
{
	ShuffledDeck = Deck;

	ShuffleArray(ShuffledDeck);
}

// シャッフル
void ADeckManager::ShuffleArray(TArray<UCardData*>& Array)
{
	for (int32 i = Array.Num() - 1; i > 0; --i)
	{
		int32 j = FMath::RandRange(0, i);
		Array.Swap(i, j);
	}
}