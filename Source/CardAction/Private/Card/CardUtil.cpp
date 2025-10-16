// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/CardUtil.h"

void UCardUtil::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// C++でDataAssetをロードして設定
	static ConstructorHelpers::FObjectFinder<UCardUtilData> CardDataAsset(TEXT("/Game/CardAction/Card/UtilData/DA_CardUtilData.DA_CardUtilData"));
	if (CardDataAsset.Succeeded())
	{
		CardUtilData = CardDataAsset.Object;
	}
}

// レアリティに紐づくカードベース画像を取得
UTexture2D* UCardUtil::GetCardBaseTexture(ECardRarityType Rarity)
{
	if (CardUtilData == nullptr)
		return nullptr;

	for (const auto& Data : CardUtilData->RarityCardBaseData)
	{
		if (Data.Rarity == Rarity)
		{
			return Data.CardBaseTexture;
		}
	}

	return nullptr;
}

// 攻撃属性に紐づくアイコン画像取得
UTexture2D* UCardUtil::GetElementTypeIconTexture(EAttackElementType ElementType)
{
	if (CardUtilData == nullptr)
		return nullptr;

	for (const auto& Data : CardUtilData->ElementTypeIconData)
	{
		if (Data.AttackElementType == ElementType)
		{
			return Data.IconTexture;
		}
	}

	return nullptr;
}

// カードタイプに紐づくアイコン画像取得
UTexture2D* UCardUtil::GetCardTypeIconTexture(ECardType CardType)
{
	if (CardUtilData == nullptr)
		return nullptr;

	for (const auto& Data : CardUtilData->CardTypeIconData)
	{
		if (Data.CardType == CardType)
		{
			return Data.IconTexture;
		}
	}

	return nullptr;
}
