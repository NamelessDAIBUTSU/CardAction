// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map/Stage/StageData.h"
#include "Card/CardData.h"
#include <Grid/GridData.h>
#include "StageObject.generated.h"

/// <summary>
/// ステージの実体
/// </summary>
UCLASS()
class CARDACTION_API UStageObject : public UObject
{
	GENERATED_BODY()
	
public:
	FVector2D GetPos() const { return Pos; }
	void SetPos(FVector2D P) { Pos = P; }

	// 繋がっているステージの取得
	TArray<UStageObject*> GetChainedStageList() const {return ChainedStageList;}
	TArray<UStageObject*> GetPreStageList() const {return PreStageList;}

	// ステージリストに追加
	void AddChainedStage(UStageObject* ChainedStage);
	void AddPreStage(UStageObject* PreStage);

	// ステージ状況の取得
	EStageCondition GetStageCondition() const { return Condition; }
	void SetStageCondition(EStageCondition Cond) { Condition = Cond; }

	// ステージタイプ
	EStageType GetStageType() const { return StageType; }
	void SetStageType(EStageType Type) { StageType = Type; }

	// グリッド情報
	UGridData* GetGridData() const { return GenerateGridData; }
	void SetGridData(UGridData* Data) { GenerateGridData = Data; }

	// 出現させる敵クラスを設定
	void SetupEnemyClass(class UMapObject* Map);
	TArray<TSubclassOf<class AEnemyBase>> GetEnemyClassList() const { return GenerateEnemyClassList; }

private:
	// ステージタイプ
	UPROPERTY()
	EStageType StageType;

	// 確定報酬カード
	UPROPERTY();
	UCardData* FixedRewardCard = nullptr;

	// ステージ状況
	UPROPERTY();
	EStageCondition Condition = EStageCondition::NotSelect;

	// ステージの高さ・幅
	UPROPERTY();
	FVector2D Pos;

	// 繋がっているステージのポインタ(前方向)
	UPROPERTY();
	TArray<UStageObject*> ChainedStageList;
	// 繋がっているステージのポインタ(後ろ方向)
	UPROPERTY();
	TArray<UStageObject*> PreStageList;

	// グリッド情報
	UPROPERTY();
	UGridData* GenerateGridData = nullptr;

	// 出現する敵のリスト
	UPROPERTY();
	TArray<TSubclassOf<class AEnemyBase>> GenerateEnemyClassList;
};
