// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/SizeBox.h>
#include <Components/TextBlock.h>
#include "CardSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// ������
	virtual void NativeConstruct() override;

public:
	// �X���b�g�ɃJ�[�h��ݒ�
	void SetupCardSlot(class UCardData* Data);

	// �J�[�h�I���A�j���[�V�����Đ�
	void PlaySelectAnim();
	// �J�[�h�I�������A�j���[�V�����Đ�
	void PlayUnSelectAnim();

	// ���ʔ���
	void ExecuteEffect();

	// �J�[�h�E�B�W�F�b�g�̃A�j���[�V�������f�t�H���g�ɖ߂�
	void PlayDefaultAnimation();

public:
	// �J�[�h�N���X
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CardWidgetClass;

	// �J�[�h�E�B�W�F�b�g
	class UCardWidget* CardWidget;

	// �z�u�p�T�C�Y�{�b�N�X
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox;

	// �A�j���[�V����
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SelectAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* UnSelectAnim;

	bool bIsSelected = false;
};
