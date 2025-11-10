// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Map/MapDef.h"
#include "MapData.generated.h"

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
	// レベル名
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

	// 何マップ目として生成可能か
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinMapNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxMapNum;

	// スポーン可能の敵
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<AEnemyBase>> SpawnableEnemy;
	
	// このマップで使うグリッドセルのデフォルトマテリアル
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* DefaultMaterial = nullptr;

	// ヘッダー / フッター / ベース画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* HeaderImage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FooterImage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BaseImage = nullptr;
};

UCLASS()
class CARDACTION_API UGenerateMapDataList : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMapData*> MapDataList;
};
