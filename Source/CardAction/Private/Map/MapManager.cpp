// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapManager.h"
#include "DrawDebugHelpers.h"

UMapManager::UMapManager()
{
	// DataAssetをロードして設定
	static ConstructorHelpers::FObjectFinder<UGenerateMapDataList> GenMapDataAsset(TEXT("/Game/CardAction/Map/DA_GenMapDataList.DA_GenMapDataList"));
	if (GenMapDataAsset.Succeeded())
	{
		GenMapDataListAsset = GenMapDataAsset.Object;
	}
}

// 初期化
void UMapManager::Initialize()
{
	if (bIsInitialized)
		return;

	// 生成するマップの生成データを初期化
	SetupGenerateMapData();

	// ステージジェネレーターの生成
	StageGenerator = NewObject<UStageGenerator>(this, UStageGenerator::StaticClass());

	bIsInitialized = true;
}

// 更新
void UMapManager::Update(float DeltaSec)
{
	if (CurrentMap == nullptr)
		return;
	
}

// マップ生成
void UMapManager::GenerateMap()
{
	if (StageGenerator == nullptr || GenMapDataList.Num() <= CurrentMapIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Map Generate is Failed."));
		return;
	}

	// マップの生成
	CurrentMap = NewObject<UMapObject>(this, UMapObject::StaticClass());
	if (CurrentMap == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Map Generate is Failed."));
		return;
	}

	// マップの初期化
	CurrentMap->Initialize(GenMapDataList[CurrentMapIndex]);

	// ステージジェネレータの初期化
	StageGenerator->Initialize(CurrentMap);

	// ボスステージの作成
	StageGenerator->GenerateBossStage();

	// 他ステージの作成と繋ぎ処理
	bool bIsSuccess = StageGenerator->GenerateChainedStage(nullptr);
	UE_LOG(LogTemp, Warning, TEXT("Map Generate is %hs"), bIsSuccess ? "Success." : "Failed.");
}

// マップを進める
void UMapManager::GoNextMap()
{
	CurrentMapIndex++;

	// 最終マップをクリアしたか判定
	if (CurrentMapIndex >= NEED_CLEAR_MAP_NUM)
	{
		bIsClearAllMap = true;
	}
}

// ステージ状況の更新
void UMapManager::RefleshStageCondition()
{
	if (CurrentMap == nullptr)
		return;

	// 一旦選択可能ステージをすべて選択不可に変更
	for (UStageObject* Stage : CurrentMap->GetStageList())
	{
		if (Stage->GetStageCondition() == EStageCondition::CanSelect)
		{
			Stage->SetStageCondition(EStageCondition::NotSelect);
		}
	}

	if (UStageObject* CurrentStage = CurrentMap->GetCurrentStage())
	{
		// クリア済みに変更
		CurrentStage->SetStageCondition(EStageCondition::Clear);

		// 繋がっているステージを選択可能に変更
		for (UStageObject* ChainedStage : CurrentStage->GetChainedStageList())
		{
			ChainedStage->SetStageCondition(EStageCondition::CanSelect);
		}
	}
}

// レベル名の取得
FName UMapManager::GetCurrentLevelName()
{
	if (CurrentMap == nullptr || CurrentMap->GetMapData() == nullptr)
		return FName();

	return CurrentMap->GetMapData()->LevelName;
}

// マップ名の取得
FName UMapManager::GetCurrentMapName()
{
	if (CurrentMap == nullptr || CurrentMap->GetMapData() == nullptr)
		return FName();

	return CurrentMap->GetMapData()->MapName;
}

// クリア判定
bool UMapManager::IsClearCurrentMap()
{
	if (CurrentMap == nullptr)
		return false;

	UStageObject* CurrentStage = CurrentMap->GetCurrentStage();
	if (CurrentStage == nullptr)
		return false;

	return CurrentStage->GetStageCondition() == EStageCondition::Clear && CurrentStage->GetChainedStageList().IsEmpty();
}

// 生成マップのデータをランダムに設定
void UMapManager::SetupGenerateMapData() 
{
	if (GenMapDataListAsset == nullptr)
		return;

	const auto& MapDataList = GenMapDataListAsset->MapDataList;

	TArray<int32> IndexBuffer;
	for (int i = 0;i < NEED_CLEAR_MAP_NUM;++i)
	{
		int32 RandomIndex = FMath::RandRange(0, MapDataList.Num() - 1);

		bool bCanGenerate = MapDataList[RandomIndex]->MinMapNum <= i && i <= MapDataList[RandomIndex]->MaxMapNum;

		// すでに抽選済みであれば再抽選
		while (IndexBuffer.Find(RandomIndex) != INDEX_NONE || bCanGenerate == false)
		{
			RandomIndex = FMath::RandRange(0, MapDataList.Num() - 1);
			bCanGenerate = MapDataList[RandomIndex]->MinMapNum <= i && i <= MapDataList[RandomIndex]->MaxMapNum;
		}

		// 生成するマップデータリストに追加
		GenMapDataList.Add(MapDataList[RandomIndex]);

		IndexBuffer.Add(RandomIndex);
	}
}

// ステージの取得
UStageObject* UMapManager::GetCurrentStage() const
{
	if (CurrentMap == nullptr)
		return nullptr;

	return CurrentMap->GetCurrentStage();
}