// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/StageSelectController.h"

AStageSelectController::AStageSelectController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AStageSelectController::BeginPlay()
{
	Super::BeginPlay();

	// �}�b�v�E�B�W�F�b�g�̐���
	if (MapWidgetClass)
	{
		MapWidget = CreateWidget<UMapWidget>(GetWorld(), MapWidgetClass);
		if (MapWidget)
		{
			MapWidget->AddToViewport();
			MapWidget->PlayInAnim();
		}
	}
}

void AStageSelectController::Tick(float DeltaSec)
{
	Super::Tick(DeltaSec);

}