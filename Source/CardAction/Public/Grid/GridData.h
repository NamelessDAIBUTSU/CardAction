// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Grid/Cell/GridCellActor.h"
#include "Map/MapDef.h"
#include "GridData.generated.h"

// 1行のグリッドデータ
USTRUCT(BlueprintType)
struct FGridRow
{
	GENERATED_BODY()

	// 1行分のセル配列
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AGridCellActor>> RowCells;
};

// 全体のグリッドデータ
UCLASS(BlueprintType)
class CARDACTION_API UGridData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// 配置するグリッドセル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<FGridRow> GridCellActors;

	// プレイヤーのスポーンさせる座標
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FCoord PlayerSpawnCoord;

	// エネミースポーン可能の座標配列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<FCoord> EnemySpawnableCoords;

	// エネミースポーン数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int SpawnEnemyNum = 1;

	// 何マップ目で生成可能か
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int MinGenMapNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int MaxGenMapNum = NEED_CLEAR_MAP_NUM - 1;
};

// グリッドデータリスト
UCLASS(BlueprintType)
class CARDACTION_API UGridDataList : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<UGridData*> GridDataList;
};