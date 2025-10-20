// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/Button.h>
#include "StageClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageClearWidget : public UHUDBase
{
	GENERATED_BODY()

public:
	// ������
	virtual bool Initialize() override;

public: /* UHUDBase */
	virtual void PlayInAnimation() override;
	virtual void PlayOutAnimation() override;

	virtual void OnUpdate(float DeltaSec) override {}

public:
	// ����{�^���������̃R�[���o�b�N
	UFUNCTION()
	void OnDecide();

	// �A�j���[�V�����I�����̃R�[���o�b�N
	UFUNCTION()
	void OnFinishOutAnim();


private:
	// ����{�^��
	UPROPERTY(meta = (BindWidget))
	UButton* DecideButton;

	bool bIsPlayingOutAnim = false;
};
