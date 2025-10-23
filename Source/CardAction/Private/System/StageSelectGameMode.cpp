// Fill out your copyright notice in the Description page of Project Settings.


#include "System/StageSelectGameMode.h"
#include <Map/MapManager.h>
#include "Map/MapData.h"

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
	if (MapManager)
	{
		// �}�b�v�}�l�[�W���[�̏�����
		MapManager->Initialize(GenerateMapData);

		// �}�b�v���������Ȃ琶������
		if (MapManager->GetCurrentMap() == nullptr)
		{
			MapManager->GenerateMap();
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
