// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/CanvasPanel.h>
#include "StageWidget.h"
#include "Map/Stage/StageObject.h"
#include "MapWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMapWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// �X�e�[�W�ǉ����邽�߂̊e��ϐ��ݒ�
	void SetupInfo();

	// �L�����o�X�ɃX�e�[�W��ǉ�
	void CreateStageWidget(UStageObject* Stage);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> StageWidgetClass;

	// �z�u�I�t�Z�b�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetX = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetY = 150.f;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* StageCanvas = nullptr;

	// �X�e�[�W�Ԃ̋���
	float StageDistX = 0.f;
	float StageDistY = 0.f;
	// �����X�e�[�W�̍��W
	float StartPosX = 0.f;
	float StartPosY = 0.f;
};
