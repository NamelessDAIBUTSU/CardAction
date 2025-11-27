// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/CardUtil.h"

UCardUtil::UCardUtil()
{
	// C++でDataAssetをロードして設定
	static ConstructorHelpers::FObjectFinder<UCardUtilData> CardDataAsset(TEXT("/Game/CardAction/Card/UtilData/DA_CardUtilData.DA_CardUtilData"));
	if (CardDataAsset.Succeeded())
	{
		CardUtilData = CardDataAsset.Object;
	}
}

void UCardUtil::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
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

// レア度に対応するカラーを取得
FSlateColor UCardUtil::GetRarityColor(ECardRarityType Rarity)
{
	FSlateColor Color;

	switch (Rarity)
	{
	case ECardRarityType::Common:
		Color = FSlateColor(FLinearColor(1.f, 1.f, 1.f));
		break;
	case ECardRarityType::Rare:
		Color = FSlateColor(FColor(10, 20, 100));
		break;
	case ECardRarityType::Epic:
		Color = FSlateColor(FColor(150, 0.f, 255));
		break;
	case ECardRarityType::Legendary:
		Color = FSlateColor(FLinearColor::Yellow);
		break;
	case ECardRarityType::Mithic:
		Color = FSlateColor(FColor::Silver);
		break;
	default:
		break;
	}

	return Color;
}

// 属性に対応するカラーを取得
FSlateColor UCardUtil::GetElementColor(EAttackElementType Element)
{
	FSlateColor Color;

	switch (Element)
	{
	case EAttackElementType::Fire:
		Color = FSlateColor(FLinearColor(1.f, 0.f, 0.f));
		break;
	case EAttackElementType::Water:
		Color = FSlateColor(FColor(0, 30, 200));
		break;
	case EAttackElementType::Thunder:
		Color = FSlateColor(FLinearColor(1.f, 1.f, 0.f));
		break;
	case EAttackElementType::Wind:
		Color = FSlateColor(FLinearColor(0.f, 1.f, 0.f));
		break;
	default:
		break;
	}

	return Color;
}
