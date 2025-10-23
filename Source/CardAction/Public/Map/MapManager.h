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
	void Initialize(UMapData* GenMapData);

	// �X�V
	void Update(float DeltaSec);

	// �}�b�v����
	void GenerateMap();

	// �}�b�v�̎擾
	UMapObject* GetCurrentMap() const { return CurrentMap; }

	// �X�e�[�W�󋵂̍X�V
	void RefleshStageCondition();

	// ���x�����̎擾
	FName GetCurrentLevelName();

private:
	// �X�e�[�W�W�F�l���[�^
	UPROPERTY()
	UStageGenerator* StageGenerator = nullptr;

	// ��������}�b�v�̏��
	UPROPERTY()
	UMapData* GenerateMapData = nullptr;

	// ���݂̃}�b�v
	UPROPERTY()
	UMapObject* CurrentMap = nullptr;
};
