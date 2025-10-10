// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/CardDeck.h"

// カードの追加
void UCardDeck::AddToDeck(UCardData* NewCard)
{
	Deck.Add(NewCard);
}

// カードの除去
void UCardDeck::RemoveFromDeck(UCardData* RemoveCard)
{
	Deck.Remove(RemoveCard);
}
