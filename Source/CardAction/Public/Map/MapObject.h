// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MapObject.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMapObject : public UObject
{
	GENERATED_BODY()
	
public:
	// マップをクリアしたか
	bool IsClear() { return false; }

	// マップサイズ
	FVector2D GetSize() const { return Size; }
	void SetSize(FVector2D S) { Size = S; }

	// 指定位置のステージを取得
	class UStageObject* GetStage(FVector2D Pos);

	// ステージの取得
	const TArray<UStageObject*>& GetStageList() const { return StageList; }

	// ステージリストに追加
	void AddStageList(class UStageObject* Stage);

	// 現在のステージ
	void SetCurrentStage(UStageObject* Stage) { CurrentStage = Stage; }
	UStageObject* GetCurrentStage() { return CurrentStage; }

private:
	// マップデータ
	UPROPERTY();
	class UMapData* MapData = nullptr;

	// 現在のステージ
	UPROPERTY();
	class UStageObject* CurrentStage = nullptr;

	// 全ステージ
	UPROPERTY();
	TArray<UStageObject*> StageList;

	// 何マップ目
	UPROPERTY();
	int MapNum = 0;

	// マップの高さ・幅
	UPROPERTY();
	FVector2D Size;
};
