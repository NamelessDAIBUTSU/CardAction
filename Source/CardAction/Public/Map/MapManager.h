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
	void Initialize();

	// 更新
	void Update(float DeltaSec);

	// マップ生成
	void GenerateMap();

	// マップを進める
	void GoNextMap();

	// マップの取得
	UMapObject* GetCurrentMap() const { return CurrentMap; }
	void ResetCurrentMap() { CurrentMap = nullptr; }

	// ステージの取得
	UStageObject* GetCurrentStage() const;

	// ステージ状況の更新
	void RefleshStageCondition();

	// レベル名の取得
	FName GetCurrentLevelName();

	// マップ名の取得
	FName GetCurrentMapName();

	// クリア判定
	bool IsClearCurrentMap();
	bool IsClearAllMap() const { return bIsClearAllMap; }

private:
	// 生成マップのデータをランダムに設定
	void SetupGenerateMapData();

private: /* アセット */
	// 生成可能マップデータリスト
	UPROPERTY()
	UGenerateMapDataList* GenMapDataListAsset = nullptr;

private:
	// ステージジェネレータ
	UPROPERTY()
	UStageGenerator* StageGenerator = nullptr;

	// 生成するマップデータリス
	UPROPERTY()
	TArray<UMapData*> GenMapDataList;

	// 現在のマップ
	UPROPERTY()
	UMapObject* CurrentMap = nullptr;

	// 初期化済みか
	UPROPERTY()
	bool bIsInitialized = false;
	
	// 現在のマップインデックス
	UPROPERTY()
	int32 CurrentMapIndex = 0;

	// 全マップクリアしたか
	bool bIsClearAllMap = false;
};
