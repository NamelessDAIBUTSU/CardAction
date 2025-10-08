// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Grid/Cell/GridCellActor.h"
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
	FVector2D PlayerSpawnCoord;

	// エネミースポーン可能の座標配列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<FVector2D> EnemySpawnableCoords;
};
