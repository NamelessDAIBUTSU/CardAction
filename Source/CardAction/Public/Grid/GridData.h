// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Grid/Cell/GridCellActor.h"
#include "GridData.generated.h"

// 1�s�̃O���b�h�f�[�^
USTRUCT(BlueprintType)
struct FGridRow
{
	GENERATED_BODY()

	// 1�s���̃Z���z��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AGridCellActor>> RowCells;
};

// �S�̂̃O���b�h�f�[�^
UCLASS(BlueprintType)
class CARDACTION_API UGridData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// �z�u����O���b�h�Z��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<FGridRow> GridCellActors;

	// �v���C���[�̃X�|�[����������W
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FVector2D PlayerSpawnCoord;

	// �G�l�~�[�X�|�[���\�̍��W�z��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<FVector2D> EnemySpawnableCoords;
};
