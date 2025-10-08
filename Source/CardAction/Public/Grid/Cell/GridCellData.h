// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid/Cell/GridCellDef.h"
#include "GridCellData.generated.h"

USTRUCT(BlueprintType)
struct CARDACTION_API FGridCellData
{
	GENERATED_BODY()

	// �O���b�h���̍��W
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D GridCoord;

	// �Z���̎��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGridCellType GridCellType = EGridCellType::Normal;

	// �Z���ɏ���Ă���A�N�^�[���
	UPROPERTY()
	TArray<AActor*> Objects;

	// �}�e���A��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterial* DefaultMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterial* DamegeSignMaterial = nullptr;
};
