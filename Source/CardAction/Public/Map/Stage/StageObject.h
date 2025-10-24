// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Map/Stage/StageData.h"
#include "Card/CardData.h"
#include "StageObject.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageObject : public UObject
{
	GENERATED_BODY()
	
public:
	FVector2D GetPos() const { return Pos; }
	void SetPos(FVector2D P) { Pos = P; }

	// �q�����Ă���X�e�[�W�̎擾
	TArray<UStageObject*> GetChainedStageList() const {return ChainedStageList;}
	TArray<UStageObject*> GetPreStageList() const {return PreStageList;}

	// �X�e�[�W���X�g�ɒǉ�
	void AddChainedStage(UStageObject* ChainedStage);
	void AddPreStage(UStageObject* PreStage);

	// �X�e�[�W�󋵂̎擾
	EStageCondition GetStageCondition() const { return Condition; }
	void SetStageCondition(EStageCondition Cond) { Condition = Cond; }

	// �X�e�[�W�^�C�v
	EStageType GetStageType() const { return StageType; }
	void SetStageType(EStageType Type) { StageType = Type; }

private:
	// �X�e�[�W�^�C�v
	UPROPERTY()
	EStageType StageType;

	// �m���V�J�[�h
	UPROPERTY();
	UCardData* FixedRewardCard = nullptr;

	// �X�e�[�W��
	UPROPERTY();
	EStageCondition Condition = EStageCondition::NotSelect;

	// �X�e�[�W�̍����E��
	UPROPERTY();
	FVector2D Pos;

	// �q�����Ă���X�e�[�W�̃|�C���^(�O����)
	UPROPERTY();
	TArray<UStageObject*> ChainedStageList;
	// �q�����Ă���X�e�[�W�̃|�C���^(������)
	UPROPERTY();
	TArray<UStageObject*> PreStageList;

	// �O���b�h���
	UPROPERTY();
	class UGridData* GenerateGridData = nullptr;

	// �o������G�̃��X�g
	UPROPERTY();
	TArray<class AEnemyBase*> GenerateEnemyList;
};
