// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageClearWidget.h"

void UStageClearWidget::PlayInAnimation()
{
	PlayAnimation(InAnim);
}


void UStageClearWidget::PlayOutAnimation()
{
	PlayAnimation(OutAnim);
}
