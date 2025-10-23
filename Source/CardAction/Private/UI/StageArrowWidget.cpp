// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StageArrowWidget.h"

void UStageArrowWidget::PlayHideAnim()
{
	if (HideAnim)
	{
		StopAnimation(IdleAnim);
		PlayAnimation(HideAnim);
	}
}

void UStageArrowWidget::PlayIdleAnim()
{
	if (IdleAnim)
	{
		StopAnimation(HideAnim);
		PlayAnimation(IdleAnim, 0.f, 5);
	}
}
