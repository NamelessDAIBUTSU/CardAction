// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Map/MapDef.h"
#include "MapData.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMapData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// �}�b�v�̎��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMapType MapType;

	// �}�b�v��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MapName;

	// �g�p���x����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;

	// �X�e�[�W�̍���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;

	// �X�e�[�W�̕��̍ŏ��E�ő�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxWidth;
	
	// ���̃}�b�v�Ŏg���O���b�h�Z���̃f�t�H���g�}�e���A��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* DefaultMaterial = nullptr;
};
