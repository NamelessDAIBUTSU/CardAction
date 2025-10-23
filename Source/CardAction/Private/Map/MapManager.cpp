// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapManager.h"
#include "DrawDebugHelpers.h"

UMapManager::UMapManager()
{
}

// ������
void UMapManager::Initialize(UMapData* GenMapData)
{
	// �X�e�[�W�W�F�l���[�^�[�̐���
	if (StageGenerator == nullptr)
	{
		StageGenerator = NewObject<UStageGenerator>(this, UStageGenerator::StaticClass());
	}

	GenerateMapData = GenMapData;
}

// �X�V
void UMapManager::Update(float DeltaSec)
{
	if (CurrentMap == nullptr)
		return;
	const auto& Stages = CurrentMap->GetStageList();
	for (int i = 0;i < Stages.Num();++i)
	{
		auto Pos = Stages[i]->GetPos();

		// ���̂̒��S���W
		FVector Center = FVector(100.f * Pos.X, 100.f * Pos.Y, 50.f);

		// ���a
		float Radius = 30.f;

		// �Z�O�����g���i���炩���j
		int32 Segments = 4;

		// ���̐F
		FColor Color = FColor::Red;

		// �f�o�b�O�`��̑������ԁi�b�j
		// 0�Ȃ�1�t���[�������A���Ȃ�i��
		float Duration = 2.f;

		// �[�x�e�X�g���s�����ifalse�ɂ���ƕǉz���ł�������j
		bool bPersistentLines = false;

		DrawDebugSphere(GetWorld(), Center, Radius, Segments, Color, bPersistentLines, Duration);

		// �q�����Ă��镔����
		const auto& ChainedStages = Stages[i]->GetChainedStageList();
		for (int j = 0;j < ChainedStages.Num(); ++j)
		{
			auto Offset = (ChainedStages[j]->GetPos() - Pos) * 0.5f;
			auto StageCenter = ChainedStages[j]->GetPos() - Offset;

			FVector NextCenter = FVector(100.f * StageCenter.X, 100.f * StageCenter.Y + 10.f * j - 1, 50.f);
			Radius = 15.f;

			Color = FColor::Blue;
			DrawDebugSphere(GetWorld(), NextCenter, Radius, Segments, Color, bPersistentLines, Duration);
		}
	}
}

// �}�b�v����
void UMapManager::GenerateMap()
{
	if (StageGenerator == nullptr || GenerateMapData == nullptr)
		return;

	// �}�b�v�̐���
	CurrentMap = NewObject<UMapObject>(this, UMapObject::StaticClass());
	if (CurrentMap == nullptr)
		return;

	// �X�e�[�W�W�F�l���[�^�̏�����
	StageGenerator->Initialize(CurrentMap);

	// �}�b�v�T�C�Y�����߂�
	int Width = FMath::RandRange(GenerateMapData->MinWidth, GenerateMapData->MaxWidth);
	CurrentMap->SetSize(FVector2D(Width, GenerateMapData->Height));

	// �S�X�e�[�W�̍쐬
	bool bIsSuccess = StageGenerator->GenerateChainedStage(nullptr);
	UE_LOG(LogTemp, Warning, TEXT("Map Generate is %hs"), bIsSuccess ? "Success." : "Failed.");
}

// �X�e�[�W�󋵂̍X�V
void UMapManager::RefleshStageCondition()
{
	if (CurrentMap == nullptr)
		return;

	// ��U�I���\�X�e�[�W�����ׂđI��s�ɕύX
	for (UStageObject* Stage : CurrentMap->GetStageList())
	{
		if (Stage->GetStageCondition() == EStageCondition::CanSelect)
		{
			Stage->SetStageCondition(EStageCondition::NotSelect);
		}
	}

	if (UStageObject* CurrentStage = CurrentMap->GetCurrentStage())
	{
		// �N���A�ς݂ɕύX
		CurrentStage->SetStageCondition(EStageCondition::Clear);

		// �q�����Ă���X�e�[�W��I���\�ɕύX
		for (UStageObject* ChainedStage : CurrentStage->GetChainedStageList())
		{
			ChainedStage->SetStageCondition(EStageCondition::CanSelect);
		}
	}
}

// ���x�����̎擾
FName UMapManager::GetCurrentLevelName()
{
	if (GenerateMapData == nullptr)
		return FName();

	return GenerateMapData->LevelName;
}
