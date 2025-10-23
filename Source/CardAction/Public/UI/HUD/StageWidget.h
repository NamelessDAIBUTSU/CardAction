// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include "Map/Stage/StageObject.h"
#include "StageWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	void PlayConditionAnim();

	void SetStageObject(UStageObject* S) { Stage = S; }
	
private: /* �A�j���[�V���� */
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Clear;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* NotSelect;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* CanSelect;

private:
	// �X�e�[�W�I�u�W�F�N�g
	UStageObject* Stage = nullptr;
};
