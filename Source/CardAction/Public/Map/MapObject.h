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
	// �}�b�v���N���A������
	bool IsClear() { return false; }

	// �}�b�v�T�C�Y
	FVector2D GetSize() const { return Size; }
	void SetSize(FVector2D S) { Size = S; }

	// �w��ʒu�̃X�e�[�W���擾
	class UStageObject* GetStage(FVector2D Pos);

	// �X�e�[�W�̎擾
	const TArray<UStageObject*>& GetStageList() const { return StageList; }

	// �X�e�[�W���X�g�ɒǉ�
	void AddStageList(class UStageObject* Stage);

	// ���݂̃X�e�[�W
	void SetCurrentStage(UStageObject* Stage) { CurrentStage = Stage; }
	UStageObject* GetCurrentStage() { return CurrentStage; }

private:
	// �}�b�v�f�[�^
	UPROPERTY();
	class UMapData* MapData = nullptr;

	// ���݂̃X�e�[�W
	UPROPERTY();
	class UStageObject* CurrentStage = nullptr;

	// �S�X�e�[�W
	UPROPERTY();
	TArray<UStageObject*> StageList;

	// ���}�b�v��
	UPROPERTY();
	int MapNum = 0;

	// �}�b�v�̍����E��
	UPROPERTY();
	FVector2D Size;
};
