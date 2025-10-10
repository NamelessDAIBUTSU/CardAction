// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardData.h"
#include "InitDeckData.h"
#include "DeckManager.generated.h"

UCLASS()
class CARDACTION_API ADeckManager : public AActor
{
	GENERATED_BODY()
	
public:
	// ������
	void Initialzie(UInitDeckData* InitDeckData);

	// �J�[�h�̒ǉ�
	void AddToDeck(UCardData* NewCard);
	// �J�[�h�̏���
	void RemoveFromDeck(UCardData* RemoveCard);

private:
	UPROPERTY(VisibleAnywhere, Category = "Card")
	TArray<UCardData*> Deck;
};
