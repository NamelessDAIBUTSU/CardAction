// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StageObject.h"
#include <Grid/GridData.h>
#include "StageGenerator.generated.h"

/// <summary>
/// ステージの内部情報を生成するジェネレータ
/// </summary>
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

	// ボスステージ生成
	void GenerateBossStage();

	// ステージ情報生成
	void GenerateStageInfo(UStageObject* TargetStage);

private:
	UPROPERTY()
	UMapObject* TargetMap = nullptr;

	UPROPERTY()
	UStageObject* BossStage = nullptr;

	// 生成可能グリッドデータリスト
	UPROPERTY()
	UGridDataList* GenGridDataList = nullptr;
};
