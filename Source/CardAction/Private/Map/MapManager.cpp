// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapManager.h"
#include "DrawDebugHelpers.h"

UMapManager::UMapManager()
{
}

// 初期化
void UMapManager::Initialize(UMapData* GenMapData)
{
	// ステージジェネレーターの生成
	if (StageGenerator == nullptr)
	{
		StageGenerator = NewObject<UStageGenerator>(this, UStageGenerator::StaticClass());
	}

	GenerateMapData = GenMapData;
}

// 更新
void UMapManager::Update(float DeltaSec)
{
	if (CurrentMap == nullptr)
		return;
	const auto& Stages = CurrentMap->GetStageList();
	for (int i = 0;i < Stages.Num();++i)
	{
		auto Pos = Stages[i]->GetPos();

		// 球体の中心座標
		FVector Center = FVector(100.f * Pos.X, 100.f * Pos.Y, 50.f);

		// 半径
		float Radius = 30.f;

		// セグメント数（滑らかさ）
		int32 Segments = 4;

		// 球の色
		FColor Color = FColor::Red;

		// デバッグ描画の存続時間（秒）
		// 0なら1フレームだけ、負なら永続
		float Duration = 2.f;

		// 深度テストを行うか（falseにすると壁越しでも見える）
		bool bPersistentLines = false;

		DrawDebugSphere(GetWorld(), Center, Radius, Segments, Color, bPersistentLines, Duration);

		// 繋がっている部分に
		const auto& ChainedStages = Stages[i]->GetChainedStageList();
		for (int j = 0;j < ChainedStages.Num(); ++j)
		{
			auto Offset = (ChainedStages[j]->GetPos() - Pos) * 0.5f;
			auto StageCenter = ChainedStages[j]->GetPos() - Offset;

			FVector NextCenter = FVector(100.f * StageCenter.X, 100.f * StageCenter.Y + 10.f * j - 1, 50.f);
			Radius = 15.f;

			Color = FColor::Blue;
			DrawDebugSphere(GetWorld(), NextCenter, Radius, Segments, Color, bPersistentLines, Duration);
		}
	}
}

// マップ生成
void UMapManager::GenerateMap()
{
	if (StageGenerator == nullptr || GenerateMapData == nullptr)
		return;

	// マップの生成
	CurrentMap = NewObject<UMapObject>(this, UMapObject::StaticClass());
	if (CurrentMap == nullptr)
		return;

	// ステージジェネレータの初期化
	StageGenerator->Initialize(CurrentMap);

	// マップサイズを決める
	int Width = FMath::RandRange(GenerateMapData->MinWidth, GenerateMapData->MaxWidth);
	CurrentMap->SetSize(FVector2D(Width, GenerateMapData->Height));

	// 全ステージの作成
	bool bIsSuccess = StageGenerator->GenerateChainedStage(nullptr);
	UE_LOG(LogTemp, Warning, TEXT("Map Generate is %hs"), bIsSuccess ? "Success." : "Failed.");
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
	if (GenerateMapData == nullptr)
		return FName();

	return GenerateMapData->LevelName;
}
