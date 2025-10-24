// Fill out your copyright notice in the Description page of Project Settings.


#include "System/StageSelectGameMode.h"
#include <Map/MapManager.h>
#include "Map/MapData.h"
#include <Controller/StageSelectController.h>
#include <System/FadeSystem.h>

AStageSelectGameMode::AStageSelectGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStageSelectGameMode::StartPlay()
{
	Super::StartPlay();

	if (GetWorld() == nullptr || GetWorld()->GetGameInstance() == nullptr)
		return;

	MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr)
		return;

	// マップマネージャーの初期化
	MapManager->Initialize();

	// ステージの状況を更新
	// #MEMO : マップ生成前に呼ぶ必要あり
	MapManager->RefleshStageCondition();

	// マップのクリア判定
	if (MapManager->IsClearCurrentMap())
	{
		// マップインデックスを進めて現在のマップをリセット
		MapManager->GoNextMap();
		MapManager->ResetCurrentMap();

		// 次のマップが存在するなら、フェードして再度ステージ選択レベルへ
		if(MapManager->IsClearAllMap() == false)
		{
			if (GetWorld()->GetGameInstance() == nullptr)
				return;

			UFadeSystem* FadeSystem = GetWorld()->GetGameInstance()->GetSubsystem<UFadeSystem>();
			if (FadeSystem == nullptr)
				return;

			FadeSystem->FadeOutAndOpenLevel(FName("SelectStageLevel"));
		}
		else
		{

		}

		return;
	}

	// マップが未生成なら生成する
	if (MapManager->GetCurrentMap() == nullptr)
	{
		MapManager->GenerateMap();
	}

	AStageSelectController* PC = Cast<AStageSelectController>(GetWorld()->GetFirstPlayerController());
	if (PC && PC->GetMapWidget())
	{
		// ステージウィジェット生成用の初期設定
		PC->GetMapWidget()->SetupInfo();

		// ステージウィジェットの生成
		if (UMapObject* Map = MapManager->GetCurrentMap())
		{
			for (UStageObject* Stage : Map->GetStageList())
			{
				PC->GetMapWidget()->CreateStageWidget(Stage);
			}
		}
	}
}

void AStageSelectGameMode::Tick(float DeltaSec)
{
	Super::Tick(DeltaSec);

	if (MapManager)
	{
		MapManager->Update(DeltaSec);
	}
}
