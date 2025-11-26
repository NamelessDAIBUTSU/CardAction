// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Card/CardData.h"
#include "Card/CardTypeDef.h"
#include "CardUtil.generated.h"

/// <summary>
/// カードUtilを扱うためのシングルトンクラス
/// </summary>
UCLASS()
class CARDACTION_API UCardUtil : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UCardUtil();

public:
	// レアリティに紐づくカードベース画像を取得
	UTexture2D* GetCardBaseTexture(ECardRarityType Rarity);

	// 攻撃属性に紐づくアイコン画像取得
	UTexture2D* GetElementTypeIconTexture(EAttackElementType ElementType);

	// カードタイプに紐づくアイコン画像取得
	UTexture2D* GetCardTypeIconTexture(ECardType CardType);

	// Enumに対応する表示文字列を取得する
	template<class EnumType>
	static FString CardEnumToString(EnumType Element)
	{
		return StaticEnum<EnumType>()->GetDisplayValueAsText(Element).ToString();
	}

	// レア度に対応するカラーを取得
	static FSlateColor GetRarityColor(ECardRarityType Rarity);

	// 属性に対応するカラーを取得
	static FSlateColor GetElementColor(EAttackElementType Element);

public:
	// Utilデータアセット
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCardUtilData* CardUtilData;
};
