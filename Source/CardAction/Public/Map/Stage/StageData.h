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
	// ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	// ステージの種類
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStageType StageType;

	// 繋げられるステージの最小・最大数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinChainedStageNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxChainedStageNum;
};
