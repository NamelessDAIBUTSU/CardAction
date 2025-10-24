// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapManager.h"
#include "DrawDebugHelpers.h"

UMapManager::UMapManager()
{
	// DataAsset�����[�h���Đݒ�
	static ConstructorHelpers::FObjectFinder<UGenerateMapDataList> GenMapDataAsset(TEXT("/Game/CardAction/Map/DA_GenMapDataList.DA_GenMapDataList"));
	if (GenMapDataAsset.Succeeded())
	{
		GenMapDataListAsset = GenMapDataAsset.Object;
	}
}

// ������
void UMapManager::Initialize()
{
	if (bIsInitialized)
		return;

	// ��������}�b�v�̐����f�[�^��������
	SetupGenerateMapData();

	// �X�e�[�W�W�F�l���[�^�[�̐���
	StageGenerator = NewObject<UStageGenerator>(this, UStageGenerator::StaticClass());

	bIsInitialized = true;
}

// �X�V
void UMapManager::Update(float DeltaSec)
{
	if (CurrentMap == nullptr)
		return;
	
}

// �}�b�v����
void UMapManager::GenerateMap()
{
	if (StageGenerator == nullptr || GenMapDataList.Num() <= CurrentMapIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Map Generate is Failed."));
		return;
	}

	// �}�b�v�̐���
	CurrentMap = NewObject<UMapObject>(this, UMapObject::StaticClass());
	if (CurrentMap == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Map Generate is Failed."));
		return;
	}

	// �}�b�v�̏�����
	CurrentMap->Initialize(GenMapDataList[CurrentMapIndex]);

	// �X�e�[�W�W�F�l���[�^�̏�����
	StageGenerator->Initialize(CurrentMap);

	// �{�X�X�e�[�W�̍쐬
	StageGenerator->GenerateBossStage();

	// ���X�e�[�W�̍쐬�ƌq������
	bool bIsSuccess = StageGenerator->GenerateChainedStage(nullptr);
	UE_LOG(LogTemp, Warning, TEXT("Map Generate is %hs"), bIsSuccess ? "Success." : "Failed.");
}

// �}�b�v��i�߂�
void UMapManager::GoNextMap()
{
	CurrentMapIndex++;

	// �ŏI�}�b�v���N���A����������
	if (CurrentMapIndex >= NEED_CLEAR_MAP_NUM)
	{
		bIsClearAllMap = true;
	}
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
	if (CurrentMap == nullptr || CurrentMap->GetMapData() == nullptr)
		return FName();

	return CurrentMap->GetMapData()->LevelName;
}

// �}�b�v���̎擾
FName UMapManager::GetCurrentMapName()
{
	if (CurrentMap == nullptr || CurrentMap->GetMapData() == nullptr)
		return FName();

	return CurrentMap->GetMapData()->MapName;
}

// �N���A����
bool UMapManager::IsClearCurrentMap()
{
	if (CurrentMap == nullptr)
		return false;

	UStageObject* CurrentStage = CurrentMap->GetCurrentStage();
	if (CurrentStage == nullptr)
		return false;

	return CurrentStage->GetStageCondition() == EStageCondition::Clear && CurrentStage->GetChainedStageList().IsEmpty();
}

// �����}�b�v�̃f�[�^�������_���ɐݒ�
void UMapManager::SetupGenerateMapData() 
{
	if (GenMapDataListAsset == nullptr)
		return;

	const auto& MapDataList = GenMapDataListAsset->MapDataList;

	TArray<int32> IndexBuffer;
	for (int i = 0;i < NEED_CLEAR_MAP_NUM;++i)
	{
		int32 RandomIndex = FMath::RandRange(0, MapDataList.Num() - 1);

		bool bCanGenerate = MapDataList[RandomIndex]->MinMapNum <= i && i <= MapDataList[RandomIndex]->MaxMapNum;

		// ���łɒ��I�ς݂ł���΍Ē��I
		while (IndexBuffer.Find(RandomIndex) != INDEX_NONE || bCanGenerate == false)
		{
			RandomIndex = FMath::RandRange(0, MapDataList.Num() - 1);
			bCanGenerate = MapDataList[RandomIndex]->MinMapNum <= i && i <= MapDataList[RandomIndex]->MaxMapNum;
		}

		// ��������}�b�v�f�[�^���X�g�ɒǉ�
		GenMapDataList.Add(MapDataList[RandomIndex]);

		IndexBuffer.Add(RandomIndex);
	}
}
