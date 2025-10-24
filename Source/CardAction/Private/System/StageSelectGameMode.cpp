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

	// �}�b�v�}�l�[�W���[�̏�����
	MapManager->Initialize();

	// �X�e�[�W�̏󋵂��X�V
	// #MEMO : �}�b�v�����O�ɌĂԕK�v����
	MapManager->RefleshStageCondition();

	// �}�b�v�̃N���A����
	if (MapManager->IsClearCurrentMap())
	{
		// �}�b�v�C���f�b�N�X��i�߂Č��݂̃}�b�v�����Z�b�g
		MapManager->GoNextMap();
		MapManager->ResetCurrentMap();

		// ���̃}�b�v�����݂���Ȃ�A�t�F�[�h���čēx�X�e�[�W�I�����x����
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

	// �}�b�v���������Ȃ琶������
	if (MapManager->GetCurrentMap() == nullptr)
	{
		MapManager->GenerateMap();
	}

	AStageSelectController* PC = Cast<AStageSelectController>(GetWorld()->GetFirstPlayerController());
	if (PC && PC->GetMapWidget())
	{
		UMapWidget* MapWidget = PC->GetMapWidget();

		UMapObject* Map = MapManager->GetCurrentMap();
		if (Map == nullptr)
			return;

		// �X�e�[�W�E�B�W�F�b�g�����p�̏����ݒ�
		MapWidget->SetupInfo(Map->GetMapData());

		// �X�e�[�W�E�B�W�F�b�g�̐���
		for (UStageObject* Stage : Map->GetStageList())
		{
			MapWidget->CreateStageWidget(Stage);
		}

		// �X�e�[�W���C���E�B�W�F�b�g�̐���
		MapWidget->CreateStageLineWidget();
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
