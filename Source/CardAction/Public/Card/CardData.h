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
	// ���j�[�NID
	UPROPERTY(VisibleAnywhere, Category = "Card")
	FName UniqueID;

	// �J�[�h��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FName Name;

	// �J�[�h����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Description;

	// ����G�l���M�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int ConsumeEnergy;

	// �J�[�h�摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* CardTexture;

	// ���A�x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardRarityType Rarity;

	// �J�[�h��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardType CardType;

	// ���ʃN���X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TSubclassOf<UCardEffectBase> EffectClass;
};

// ���A���e�B�J�[�h�x�[�X�p
USTRUCT(BlueprintType)
struct FRarityCardBaseData 
{
	GENERATED_BODY()

public:
	// ���A�x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardRarityType Rarity;

	// �J�[�h�x�[�X�摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* CardBaseTexture;
};

// �J�[�h�^�C�v�A�C�R���p
USTRUCT(BlueprintType)
struct FCardTypeIconData
{
	GENERATED_BODY()

public:
	// �J�[�h�^�C�v
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECardType CardType;

	// �A�C�R���摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* IconTexture;
};

// �����^�C�v�A�C�R���p
USTRUCT(BlueprintType)
struct FElementTypeIconData
{
	GENERATED_BODY()

public:
	// �J�[�h�^�C�v
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	EAttackElementType AttackElementType;

	// �A�C�R���摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UTexture2D* IconTexture;
};

UCLASS()
class CARDACTION_API UCardUtilData : public UDataAsset
{
	GENERATED_BODY()

public:
	// ���A���e�B�ɕR�Â����J�[�h�x�[�X�摜
	UPROPERTY(EditAnywhere, Category = "Card")
	TArray<FRarityCardBaseData> RarityCardBaseData;

	// �J�[�h�^�C�v�ɕR�Â����A�C�R���摜
	UPROPERTY(EditAnywhere, Category = "Card")
	TArray<FCardTypeIconData> CardTypeIconData;

	// �����^�C�v�ɕR�Â����A�C�R���摜
	UPROPERTY(EditAnywhere, Category = "Card")
	TArray<FElementTypeIconData> ElementTypeIconData;
};