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
	// �J�[�h�̒ǉ�
	void AddToDeck(UCardData* NewCard);
	// �J�[�h�̏���
	void RemoveFromDeck(UCardData* RemoveCard);

private:
	TArray<UCardData*> Deck;
};
