// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Card/CardTypeDef.h"
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
	// ユニークID
	UPROPERTY(VisibleAnywhere, Category = "Card")
	FName UniqueID;

	// カード名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FName Name;

	// カード説明
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Description;

	// 消費エネルギー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int ConsumeEnergy;

	// カード画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* CardTexture;

	// レア度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardRarityType Rarity;

	// カード種
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardType CardType;

	// 効果クラス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TSubclassOf<UCardEffectBase> EffectClass;
};

// レアリティカードベース用
USTRUCT(BlueprintType)
struct FRarityCardBaseData 
{
	GENERATED_BODY()

public:
	// レア度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardRarityType Rarity;

	// カードベース画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* CardBaseTexture;
};

// カードタイプアイコン用
USTRUCT(BlueprintType)
struct FCardTypeIconData
{
	GENERATED_BODY()

public:
	// カードタイプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardType CardType;

	// アイコン画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* IconTexture;
};

// 属性タイプアイコン用
USTRUCT(BlueprintType)
struct FElementTypeIconData
{
	GENERATED_BODY()

public:
	// カードタイプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	EAttackElementType AttackElementType;

	// アイコン画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* IconTexture;
};

UCLASS()
class CARDACTION_API UCardUtilData : public UDataAsset
{
	GENERATED_BODY()

public:
	// レアリティに紐づいたカードベース画像
	UPROPERTY(EditAnywhere, Category = "Card")
	TArray<FRarityCardBaseData> RarityCardBaseData;

	// カードタイプに紐づいたアイコン画像
	UPROPERTY(EditAnywhere, Category = "Card")
	TArray<FCardTypeIconData> CardTypeIconData;

	// 属性タイプに紐づいたアイコン画像
	UPROPERTY(EditAnywhere, Category = "Card")
	TArray<FElementTypeIconData> ElementTypeIconData;
};