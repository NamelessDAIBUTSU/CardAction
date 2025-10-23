// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageWidget.h"

void UStageWidget::PlayConditionAnim()
{
	if (Stage == nullptr)
		return;

	switch (Stage->GetStageCondition())
	{
	case EStageCondition::Clear:
		PlayAnimation(Clear);
		break;
	case EStageCondition::CanSelect:
		PlayAnimation(CanSelect);
		break;
	case EStageCondition::NotSelect:
		PlayAnimation(NotSelect);
		break;
	default:
		break;
	}
}
