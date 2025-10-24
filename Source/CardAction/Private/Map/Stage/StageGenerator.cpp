// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Stage/StageGenerator.h"
#include <Map/MapObject.h>
#include "Map/Stage/StageDef.h"

UStageGenerator::UStageGenerator()
{

}

void UStageGenerator::Initialize(UMapObject* Map)
{
	TargetMap = Map;
}

// �q����X�e�[�W����
bool UStageGenerator::GenerateChainedStage(UStageObject* PreStage)
{
	if (TargetMap == nullptr)
		return false;

	bool bIsSuccess = false;

	// �O�̃X�e�[�W�����݂��Ȃ��ꍇ�A���߂̃X�e�[�W�𐶐�
	if (PreStage == nullptr)
	{
		FName UniqueName = MakeUniqueObjectName(this, UStageObject::StaticClass());
		UStageObject* FirstStage = NewObject<UStageObject>(this, UStageObject::StaticClass(), UniqueName);
		if (FirstStage)
		{
			// �����ʒu(0, 0)��ݒ�
			FirstStage->SetPos(FVector2D(0.f, 0.f));

			PreStage = FirstStage;

			// �}�b�v�ɃX�e�[�W�ǉ�
			TargetMap->AddStageList(FirstStage);

			// ���݂̃X�e�[�W�ɐݒ�
			TargetMap->SetCurrentStage(FirstStage);
			FirstStage->SetStageCondition(EStageCondition::CanSelect);
		}
	}

	// �Ȃ��z�肾���ǈꉞ�`�F�b�N
	if (PreStage == nullptr)
		return false;

	// ���łɌq�����X�e�[�W�����݂���ꍇ������
	if (PreStage->GetChainedStageList().IsEmpty() == false)
		return false;

	// �}�b�v��-1�܂ŗ����ꍇ�̓{�X�X�e�[�W�Ɍq���Ĕ�����
	// #MEMO : 0�I���W���ŁA�{�X�X�e�[�W�����邩��-2����
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

	// �q����X�e�[�W���������_���Ɏ擾
	int32 Min = MIN_STAGE_CHAIN_NUM;
	int32 Max = MAX_STAGE_CHAIN_NUM;

	// ��������� or �����܂ŗ��Ă�����ő��2�ɂ���
	int HalfSize = (TargetMap->GetSize().Y - 1) / 2;
	if (HalfSize == PreStage->GetPos().Y || HalfSize == PreStage->GetPos().Y * -1.f)
	{
		Max = MAX_STAGE_CHAIN_NUM - 1;
	}
	int ChainNum = FMath::RandRange(Min, Max);

	TArray<int32> IndexBuffer;
	FVector2D Pos;
	Pos.X = PreStage->GetPos().X + 1;
	// �q����X�e�[�W�𐶐�
	for (int i = 0; i < ChainNum; ++i)
	{
		// ������q����X�e�[�W���Ȃ��ꍇ�A�^���Ɍq����
		if (ChainNum == 1)
		{
			Pos.Y = PreStage->GetPos().Y;
		}
		// ����ȊO�̏ꍇ�A�����_���ɍ������擾���Čq����
		else
		{
			int32 HeightMin = PreStage->GetPos().Y - 1;
			int32 HeightMax = PreStage->GetPos().Y + 1;

			// ��������� or �����܂ŗ��Ă�����O��
			if ((TargetMap->GetSize().Y - 1) / 2 == PreStage->GetPos().Y)
			{
				HeightMax -= 1;
			}
			if ((TargetMap->GetSize().Y - 1) / 2 == PreStage->GetPos().Y * -1.f)
			{
				HeightMin += 1;
			}

			int32 RandomHeight = FMath::RandRange(HeightMin, HeightMax);

			// ���łɒ��I�ς݂ł���΍Ē��I
			while (IndexBuffer.Find(RandomHeight) != INDEX_NONE)
			{
				RandomHeight = FMath::RandRange(HeightMin, HeightMax);
			}

			// �T�C�Y�m��
			Pos.Y = RandomHeight;

			// �Ē��I�p�ɃC���f�b�N�X�Ǘ�
			IndexBuffer.Add(RandomHeight);
		}

		// ���łɂ��̈ʒu�ɃX�e�[�W����������Ă�����q���邾��
		if (UStageObject* Stage = TargetMap->GetStage(Pos))
		{
			PreStage->AddChainedStage(Stage);
			Stage->AddPreStage(PreStage);
		}
		// �Ȃ�������V�K�ŃX�e�[�W����
		else
		{
			FName UniqueName = MakeUniqueObjectName(this, UStageObject::StaticClass());
			UStageObject* ChainedStage = NewObject<UStageObject>(this, UStageObject::StaticClass(), UniqueName);
			if (ChainedStage)
			{
				PreStage->AddChainedStage(ChainedStage);
				ChainedStage->AddPreStage(PreStage);

				ChainedStage->SetPos(Pos);

				// �}�b�v�ɃX�e�[�W�ǉ�
				TargetMap->AddStageList(ChainedStage);
			}
		}
	}

	// �V�K�����̊e�X�e�[�W�Ōq�����Ă���X�e�[�W�𐶐�����
	for (UStageObject* ChainedStage : PreStage->GetChainedStageList())
	{
		bIsSuccess |= GenerateChainedStage(ChainedStage);
	}

	return bIsSuccess;
}

// �{�X�X�e�[�W����
void UStageGenerator::GenerateBossStage()
{
	if (TargetMap == nullptr)
		return;

	// ����
	FName UniqueName = MakeUniqueObjectName(this, UStageObject::StaticClass());
	BossStage = NewObject<UStageObject>(this, UStageObject::StaticClass(), UniqueName);
	if (BossStage)
	{
		BossStage->SetStageType(EStageType::Boss);

		// 0�I���W���̂���-1
		BossStage->SetPos(FVector2D(TargetMap->GetSize().X - 1, 0.f));

		TargetMap->AddStageList(BossStage);
	}
}

