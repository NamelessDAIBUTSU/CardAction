// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/CanvasPanel.h>
#include "StageWidget.h"
#include "Map/Stage/StageObject.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Map/MapData.h>
#include "MapWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMapWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// �e��ϐ��ݒ�
	void SetupInfo(UMapData* Data);

	// �L�����o�X�ɃX�e�[�W��ǉ�
	void CreateStageWidget(UStageObject* Stage);

	// �L�����o�X�ɃX�e�[�W����ǉ�
	void CreateStageLineWidget();

	// �G���W������Ɨ������X�V�N���X
	virtual void OnUpdate(float DeltaSec) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> StageWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> StageLineWidgetClass;

	// �z�u�I�t�Z�b�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetX = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetY = 150.f;

private: /* �E�B�W�F�b�g */
	// �ق��E�B�W�F�b�g�ǉ��p�L�����o�X
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* StageCanvas = nullptr;

	// �}�b�v���e�L�X�g
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MapName = nullptr;

	// �w�b�_�[ / �t�b�J�[ / �w�i
	UPROPERTY(meta = (BindWidget))
	UImage* HeaderImage = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* FooterImage = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* MapBaseImage = nullptr;

private:
	// �}�b�v�f�[�^
	UPROPERTY()
	UMapData* MapData = nullptr;

	// �X�e�[�W�E�B�W�F�b�g
	UPROPERTY()
	TArray<UStageWidget*> StageWidgets;
	
	// �X�e�[�W�Ԃ̋���
	UPROPERTY()
	float StageDistX = 0.f;
	UPROPERTY()
	float StageDistY = 0.f;
	// �����X�e�[�W�̍��W
	UPROPERTY()
	float StartPosX = 0.f;
	UPROPERTY()
	float StartPosY = 0.f;
};
