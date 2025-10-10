// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardData.h"
#include "CardDeck.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardDeck : public UObject
{
	GENERATED_BODY()
	
public:
	// カードの追加
	void AddToDeck(UCardData* NewCard);
	// カードの除去
	void RemoveFromDeck(UCardData* RemoveCard);

private:
	TArray<UCardData*> Deck;
};
