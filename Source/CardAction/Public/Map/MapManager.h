// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Map/Stage/StageGenerator.h"
#include "Map/MapData.h"
#include "Map/MapObject.h"
#include "MapManager.generated.h"

UCLASS()
class CARDACTION_API UMapManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:	
	UMapManager();

public:
	// 初期化
	void Initialize(UMapData* GenMapData);

	// 更新
	void Update(float DeltaSec);

	// マップ生成
	void GenerateMap();

	// マップの取得
	UMapObject* GetCurrentMap() const { return CurrentMap; }

private:
	// ステージジェネレータ
	UPROPERTY()
	UStageGenerator* StageGenerator = nullptr;

	// 生成するマップの情報
	UPROPERTY()
	UMapData* GenerateMapData = nullptr;

	// 現在のマップ
	UPROPERTY()
	UMapObject* CurrentMap = nullptr;
};
