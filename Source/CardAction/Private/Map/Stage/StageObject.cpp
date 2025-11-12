// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Stage/StageObject.h"
#include "Map/MapObject.h"

void UStageObject::AddChainedStage(UStageObject* ChainedStage)
{
	ChainedStageList.Add(ChainedStage);
}

void UStageObject::AddPreStage(UStageObject* PreStage)
{
	PreStageList.Add(PreStage);
}

// 出現させる敵クラスを設定
void UStageObject::SetupEnemyClass(UMapObject* Map)
{
	if (GenerateGridData == nullptr)
		return;

	if (Map == nullptr || Map->GetMapData() == nullptr)
		return;

	// 出現させる敵の数を取得
	const int SpawnEnemyNum = GenerateGridData->SpawnEnemyNum;
	// 出現可能の敵リストを取得
	const auto& EnemyList = Map->GetMapData()->SpawnableEnemy;
	if (EnemyList.IsEmpty())
		return;

	// 出現させる敵クラスをランダムに取得し、リストに保存していく
	for (int i = 0; i < SpawnEnemyNum; ++i)
	{
		int Index = FMath::RandRange(0, EnemyList.Num() - 1);
		GenerateEnemyClassList.Add(EnemyList[Index]);
	}
}
