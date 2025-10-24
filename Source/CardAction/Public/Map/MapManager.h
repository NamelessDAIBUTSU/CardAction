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
	// ������
	void Initialize();

	// �X�V
	void Update(float DeltaSec);

	// �}�b�v����
	void GenerateMap();

	// �}�b�v��i�߂�
	void GoNextMap();

	// �}�b�v�̎擾
	UMapObject* GetCurrentMap() const { return CurrentMap; }
	void ResetCurrentMap() { CurrentMap = nullptr; }

	// �X�e�[�W�󋵂̍X�V
	void RefleshStageCondition();

	// ���x�����̎擾
	FName GetCurrentLevelName();

	// �}�b�v���̎擾
	FName GetCurrentMapName();

	// �N���A����
	bool IsClearCurrentMap();
	bool IsClearAllMap() const { return bIsClearAllMap; }

private:
	// �����}�b�v�̃f�[�^�������_���ɐݒ�
	void SetupGenerateMapData();


private:
	// �X�e�[�W�W�F�l���[�^
	UPROPERTY()
	UStageGenerator* StageGenerator = nullptr;

	// �����\�}�b�v�f�[�^���X�g
	UPROPERTY()
	UGenerateMapDataList* GenMapDataListAsset = nullptr;

	// ��������}�b�v�f�[�^���X
	UPROPERTY()
	TArray<UMapData*> GenMapDataList;

	// ���݂̃}�b�v
	UPROPERTY()
	UMapObject* CurrentMap = nullptr;

	// �������ς݂�
	UPROPERTY()
	bool bIsInitialized = false;
	
	// ���݂̃}�b�v�C���f�b�N�X
	UPROPERTY()
	int32 CurrentMapIndex = 0;

	// �S�}�b�v�N���A������
	bool bIsClearAllMap = false;
};
