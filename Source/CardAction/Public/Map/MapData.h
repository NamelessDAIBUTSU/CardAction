// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Map/MapDef.h"
#include "MapData.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMapData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// マップの種類
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMapType MapType;

	// マップ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MapName;

	// 使用レベル名
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;

	// ステージの高さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;

	// ステージの幅の最小・最大
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxWidth;
	
	// このマップで使うグリッドセルのデフォルトマテリアル
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* DefaultMaterial = nullptr;
};
