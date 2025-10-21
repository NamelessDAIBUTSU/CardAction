// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "CharaBannerWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCharaBannerWidget : public UHUDBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override {}

public:
	// �E�B�W�F�b�g�̐ݒ�
	void Setup(class AEnemyBase* Enemy);

	// �������C�A�E�g�ύX
	void ChangeLayout(bool IsDead);
	
private:
	// �������C�A�E�g�A�j���[�V����
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* AliveLayoutAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DeadLayoutAnim;

	// �A�C�R���C���[�W�E�B�W�F�b�g
	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	// �G�̖��O�e�L�X�g
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyNameText;
};
