// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GridCamera.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AGridCamera : public ACameraActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// �O���b�h��񂩂獂���𒲐�����֐�
	void AdjustCameraToGrid();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	float BaseHeight = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	float HeightOffset = 20.f;
};
