// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardData.h"
#include "InitDeckData.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UInitDeckData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// デッキ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FName Name;

	// デッキ説明
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Description;

	// 初期カード
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<UCardData*> Cards;
};
