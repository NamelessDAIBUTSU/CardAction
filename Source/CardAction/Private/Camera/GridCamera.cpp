// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/GridCamera.h"
#include <Grid/Cell/GridCellDef.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"

void AGridCamera::BeginPlay()
{
}

// �O���b�h��񂩂獂���𒲐�����֐�
void AGridCamera::AdjustCameraToGrid()
{
	if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
	{
		if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
		{
			if (MyGameMode->GridManager == nullptr)
				return;

			// �J�����̈ʒu���Z�o
			FVector2D GridSize = MyGameMode->GridManager->GetGridSize();
			float XPos = ((GridSize.Y + 1) * GRID_CELL_UNIT + 0.f) * -1.f;
			float YPos = ((GridSize.X - 1) * 0.5f * GRID_CELL_UNIT + 0.f);
			FVector CameraPosition = FVector(XPos, YPos, 0.f);

			// �J�����̍������O���b�h�T�C�Y�ɉ����ĕω�
			float Height = BaseHeight + GridSize.X * HeightOffset;

			SetActorLocation(FVector(CameraPosition.X, CameraPosition.Y, Height));
			SetActorRotation(FRotator(-50.f, 0.f, 0.f));
		}
	}

}
