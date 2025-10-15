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

	// �J�[�h������
	TArray<UCardData*> DrawCards();

	// �V���b�t�����ꂽ�f�b�L���쐬
	void CreateShuffledDeck();

private:
	// �V���b�t��
	void ShuffleArray(TArray<UCardData*>& Array);

private:
	// �f�b�L
	UPROPERTY(VisibleAnywhere, Category = "Card")
	TArray<UCardData*> Deck;

	// �������߂ɃV���b�t�������f�b�L
	UPROPERTY(VisibleAnywhere, Category = "Card")
	TArray<UCardData*> ShuffledDeck;

	// ���݂̃h���[�C���f�b�N�X
	UPROPERTY(VisibleAnywhere, Category = "Card")
	int DrawIndex = 0;
};
