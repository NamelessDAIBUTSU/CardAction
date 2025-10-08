// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Card/CardTypeDef.h"
#include "Card/CardRarityDef.h"
#include "Effect/CardEffectBase.h"
#include "CardData.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// カード名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FName Name;

	// カード説明
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Description;

	// 消費エネルギー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int ConsumeEnergy;

	// カード画像パス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString ImagePath;

	// レア度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardRarity Rarity;

	// 種類
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardType CardType;

	// ゲーム終了後、獲得可能か
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	bool bCanGet = true;

	// 効果
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TSubclassOf<UCardEffectBase> Effect;
};
