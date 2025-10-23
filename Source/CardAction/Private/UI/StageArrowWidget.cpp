// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StageArrowWidget.h"

void UStageArrowWidget::PlayHideAnim()
{
	if (HideAnim)
	{
		PlayAnimation(HideAnim);
	}
}

void UStageArrowWidget::PlayIdleAnim()
{
	if (IdleAnim)
	{
		PlayAnimation(IdleAnim, 0.f, 5);
	}
}
