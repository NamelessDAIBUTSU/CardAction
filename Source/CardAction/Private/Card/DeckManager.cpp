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
	Deck.Add(NewCard);
}

// カードの除去
void ADeckManager::RemoveFromDeck(UCardData* RemoveCard)
{
	Deck.Remove(RemoveCard);
}

UCardData* ADeckManager::DrawCardFromTop()
{
	if (Deck.IsEmpty())
		return nullptr;

	return *Deck.begin();
}
