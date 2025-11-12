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
	// 初期化
	void Initialzie(UInitDeckData* InitDeckData);

	// カードの追加
	void AddToDeck(UCardData* NewCard);
	// カードの除去
	void RemoveFromDeck(UCardData* RemoveCard);

	// カードを引く
	TArray<UCardData*> DrawCards();

	// シャッフルされたデッキを作成
	void CreateShuffledDeck();

private:
	// シャッフル
	void ShuffleArray(TArray<UCardData*>& Array);

private:
	// デッキ
	UPROPERTY(VisibleAnywhere, Category = "Card")
	TArray<UCardData*> Deck;

	// 引くためにシャッフルしたデッキ
	UPROPERTY(VisibleAnywhere, Category = "Card")
	TArray<UCardData*> ShuffledDeck;

	// 現在のドローインデックス
	UPROPERTY(VisibleAnywhere, Category = "Card")
	int DrawIndex = 0;
};
