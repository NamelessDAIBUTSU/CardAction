// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/Cell/GridCellDef.h"
#include "GridCellData.generated.h"

USTRUCT(BlueprintType)
struct CARDACTION_API FGridCellData
{
	GENERATED_BODY()

	// グリッド内の座標
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D GridCoord;

	// セルの種類
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGridCellType GridCellType = EGridCellType::Normal;

	// セルに乗っているアクター情報
	UPROPERTY()
	TArray<AActor*> Objects;

	// マテリアル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterial* DefaultMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterial* DamegeSignMaterial = nullptr;
};
