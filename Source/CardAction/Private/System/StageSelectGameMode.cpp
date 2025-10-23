// Fill out your copyright notice in the Description page of Project Settings.


#include "System/StageSelectGameMode.h"
#include <Map/MapManager.h>
#include "Map/MapData.h"
#include <Controller/StageSelectController.h>

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

	// �}�b�v�}�l�[�W���[�̏�����
	MapManager->Initialize(GenerateMapData);

	// �X�e�[�W�̏󋵂��X�V
	MapManager->RefleshStageCondition();

	// �}�b�v���������Ȃ琶������
	if (MapManager->GetCurrentMap() == nullptr)
	{
		MapManager->GenerateMap();
	}



	AStageSelectController* PC = Cast<AStageSelectController>(GetWorld()->GetFirstPlayerController());
	if (PC && PC->GetMapWidget())
	{
		// �X�e�[�W�E�B�W�F�b�g�����p�̏����ݒ�
		PC->GetMapWidget()->SetupInfo();

		// �X�e�[�W�E�B�W�F�b�g�̐���
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
