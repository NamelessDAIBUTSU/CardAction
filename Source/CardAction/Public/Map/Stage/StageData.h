// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Map/Stage/StageDef.h"
#include "StageData.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// �X�e�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	// �X�e�[�W�̎��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStageType StageType;

	// �q������X�e�[�W�̍ŏ��E�ő吔
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinChainedStageNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxChainedStageNum;
};
