// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Card/CardData.h"
#include "Card/CardTypeDef.h"
#include "CardUtil.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardUtil : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UCardUtil();

public:
	// ���A���e�B�ɕR�Â��J�[�h�x�[�X�摜���擾
	UTexture2D* GetCardBaseTexture(ECardRarityType Rarity);

	// �U�������ɕR�Â��A�C�R���摜�擾
	UTexture2D* GetElementTypeIconTexture(EAttackElementType ElementType);

	// �J�[�h�^�C�v�ɕR�Â��A�C�R���摜�擾
	UTexture2D* GetCardTypeIconTexture(ECardType CardType);

public:
	// Util�f�[�^�A�Z�b�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCardUtilData* CardUtilData;
};
