// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/CardDeck.h"

// �J�[�h�̒ǉ�
void UCardDeck::AddToDeck(UCardData* NewCard)
{
	Deck.Add(NewCard);
}

// �J�[�h�̏���
void UCardDeck::RemoveFromDeck(UCardData* RemoveCard)
{
	Deck.Remove(RemoveCard);
}
