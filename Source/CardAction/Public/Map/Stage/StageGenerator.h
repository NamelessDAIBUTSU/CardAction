// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StageObject.h"
#include "StageGenerator.generated.h"

// �X�e�[�W�̓������𐶐�����W�F�l���[�^
UCLASS()
class CARDACTION_API UStageGenerator : public UObject
{
	GENERATED_BODY()
	
public:	
	UStageGenerator();

public:
	// ������
	void Initialize(class UMapObject* Map);

	// �q����X�e�[�W����
	bool GenerateChainedStage(UStageObject* PreStage);

private:
	UPROPERTY()
	UMapObject* TargetMap = nullptr;
};
