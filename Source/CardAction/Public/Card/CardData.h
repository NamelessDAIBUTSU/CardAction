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

	// �J�[�h�摜�p�X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString ImagePath;

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
