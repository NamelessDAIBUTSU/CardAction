// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StageObject.h"
#include "StageGenerator.generated.h"

// ステージの内部情報を生成するジェネレータ
UCLASS()
class CARDACTION_API UStageGenerator : public UObject
{
	GENERATED_BODY()
	
public:	
	UStageGenerator();

public:
	// 初期化
	void Initialize(class UMapObject* Map);

	// 繋げるステージ生成
	bool GenerateChainedStage(UStageObject* PreStage);

private:
	UPROPERTY()
	UMapObject* TargetMap = nullptr;
};
