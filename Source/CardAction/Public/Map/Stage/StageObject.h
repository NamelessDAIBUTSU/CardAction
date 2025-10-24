// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map/Stage/StageData.h"
#include "Card/CardData.h"
#include "StageObject.generated.h"

/**
 * 
 */
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
	class UGridData* GenerateGridData = nullptr;

	// 出現する敵のリスト
	UPROPERTY();
	TArray<class AEnemyBase*> GenerateEnemyList;
};
