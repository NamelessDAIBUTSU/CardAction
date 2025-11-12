// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Stage/StageGenerator.h"
#include <Map/MapObject.h>
#include "Map/Stage/StageDef.h"

UStageGenerator::UStageGenerator()
{
	// 生成可能グリッドデータの取得
	static ConstructorHelpers::FObjectFinder<UGridDataList> GridDataAsset(TEXT("/Game/CardAction/Grid/DA_GridDataList.DA_GridDataList"));
	if (GridDataAsset.Succeeded())
	{
		GenGridDataList = GridDataAsset.Object;
	}
}

void UStageGenerator::Initialize(UMapObject* Map)
{
	TargetMap = Map;
}

// 繋げるステージ生成
bool UStageGenerator::GenerateChainedStage(UStageObject* PreStage)
{
	if (TargetMap == nullptr)
		return false;

	bool bIsSuccess = false;

	// 前のステージが存在しない場合、初めのステージを生成
	if (PreStage == nullptr)
	{
		FName UniqueName = MakeUniqueObjectName(this, UStageObject::StaticClass());
		UStageObject* FirstStage = NewObject<UStageObject>(this, UStageObject::StaticClass(), UniqueName);
		if (FirstStage)
		{
			// 初期位置(0, 0)を設定
			FirstStage->SetPos(FVector2D(0.f, 0.f));

			PreStage = FirstStage;

			// マップにステージ追加
			TargetMap->AddStageList(FirstStage);

			// 現在のステージに設定
			TargetMap->SetCurrentStage(FirstStage);
			FirstStage->SetStageCondition(EStageCondition::CanSelect);

			// ステージ情報をランダムに設定
			GenerateStageInfo(FirstStage);
		}
	}

	// ない想定だけど一応チェック
	if (PreStage == nullptr)
		return false;

	// すでに繋げたステージが存在する場合抜ける
	if (PreStage->GetChainedStageList().IsEmpty() == false)
		return false;

	// マップ幅-1まで来た場合はボスステージに繋げて抜ける
	// #MEMO : 0オリジンで、ボスステージがあるから-2する
	int PrePosX = PreStage->GetPos().X;
	int MapSizeX = TargetMap->GetSize().X;
	if (PrePosX == (MapSizeX - 2))
	{
		if (BossStage)
		{
			PreStage->AddChainedStage(BossStage);
			BossStage->AddPreStage(PreStage);
		}

		return true;
	}

	// 繋げるステージ数をランダムに取得
	int32 Min = MIN_STAGE_CHAIN_NUM;
	int32 Max = MAX_STAGE_CHAIN_NUM;

	// 高さが上限 or 下限まで来ていたら最大を2個にする
	int HalfSize = (TargetMap->GetSize().Y - 1) / 2;
	if (HalfSize == PreStage->GetPos().Y || HalfSize == PreStage->GetPos().Y * -1.f)
	{
		Max = MAX_STAGE_CHAIN_NUM - 1;
	}

	// 最初のステージであれば、最低を2個にする
	if (PreStage->GetPos().IsZero())
	{
		Min = 2;
	}

	int ChainNum = FMath::RandRange(Min, Max);

	TArray<int32> IndexBuffer;
	FVector2D Pos;
	Pos.X = PreStage->GetPos().X + 1;
	// 繋げるステージを生成
	for (int i = 0; i < ChainNum; ++i)
	{
		// 一つしか繋げるステージがない場合、真横に繋げる
		if (ChainNum == 1)
		{
			Pos.Y = PreStage->GetPos().Y;
		}
		// それ以外の場合、ランダムに高さを取得して繋げる
		else
		{
			int32 HeightMin = PreStage->GetPos().Y - 1;
			int32 HeightMax = PreStage->GetPos().Y + 1;

			// 高さが上限 or 下限まで来ていたら外す
			if ((TargetMap->GetSize().Y - 1) / 2 == PreStage->GetPos().Y)
			{
				HeightMax -= 1;
			}
			if ((TargetMap->GetSize().Y - 1) / 2 == PreStage->GetPos().Y * -1.f)
			{
				HeightMin += 1;
			}

			int32 RandomHeight = FMath::RandRange(HeightMin, HeightMax);

			// すでに抽選済みであれば再抽選
			while (IndexBuffer.Find(RandomHeight) != INDEX_NONE)
			{
				RandomHeight = FMath::RandRange(HeightMin, HeightMax);
			}

			// サイズ確定
			Pos.Y = RandomHeight;

			// 再抽選用にインデックス管理
			IndexBuffer.Add(RandomHeight);
		}

		// すでにその位置にステージが生成されていたら繋げるだけ
		if (UStageObject* Stage = TargetMap->GetStage(Pos))
		{
			PreStage->AddChainedStage(Stage);
			Stage->AddPreStage(PreStage);
		}
		// なかったら新規でステージ生成
		else
		{
			FName UniqueName = MakeUniqueObjectName(this, UStageObject::StaticClass());
			UStageObject* ChainedStage = NewObject<UStageObject>(this, UStageObject::StaticClass(), UniqueName);
			if (ChainedStage)
			{
				PreStage->AddChainedStage(ChainedStage);
				ChainedStage->AddPreStage(PreStage);

				ChainedStage->SetPos(Pos);

				// マップにステージ追加
				TargetMap->AddStageList(ChainedStage);

				// ステージ情報をランダムに設定
				GenerateStageInfo(ChainedStage);
			}
		}
	}

	// 新規生成の各ステージで繋がっているステージを生成する
	for (UStageObject* ChainedStage : PreStage->GetChainedStageList())
	{
		bIsSuccess |= GenerateChainedStage(ChainedStage);
	}

	return bIsSuccess;
}

// ボスステージ生成
void UStageGenerator::GenerateBossStage()
{
	if (TargetMap == nullptr)
		return;

	// 生成
	FName UniqueName = MakeUniqueObjectName(this, UStageObject::StaticClass());
	BossStage = NewObject<UStageObject>(this, UStageObject::StaticClass(), UniqueName);
	if (BossStage)
	{
		BossStage->SetStageType(EStageType::Boss);

		// 0オリジンのため-1
		BossStage->SetPos(FVector2D(TargetMap->GetSize().X - 1, 0.f));

		TargetMap->AddStageList(BossStage);

		// ステージ情報をランダムに設定
		GenerateStageInfo(BossStage);
	}
}

// ステージ情報生成
void UStageGenerator::GenerateStageInfo(UStageObject* TargetStage)
{
	if (GenGridDataList == nullptr || TargetMap == nullptr || TargetStage == nullptr)
		return;

	const auto& GridDataList = GenGridDataList->GridDataList;
	if (GridDataList.IsEmpty())
		return;

	// 生成できるグリッドが取得できるまでインデックスをランダム取得
	int Index = FMath::RandRange(0, GridDataList.Num() - 1);
	while (TargetMap->GetMapNum() < GridDataList[Index]->MinGenMapNum || GridDataList[Index]->MaxGenMapNum < TargetMap->GetMapNum())
	{
		Index = FMath::RandRange(0, GridDataList.Num() - 1);
	}

	// ステージに設定
	TargetStage->SetGridData(GridDataList[Index]);

	// 出現させる敵クラスをランダムに設定
	TargetStage->SetupEnemyClass(TargetMap);
}

