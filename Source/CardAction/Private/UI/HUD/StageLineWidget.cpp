// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageLineWidget.h"

void UStageLineWidget::SetPostStage(UStageObject* Post)
{
	PostStage = Post;
}

// アニメーション設定
void UStageLineWidget::SetupAnim()
{
	if (PostStage == nullptr)
		return;

	if (PostStage->GetStageCondition() == EStageCondition::CanSelect)
	{
		PlayAnimation(StageLineAnim);
	}
	else
	{
		PlayAnimation(PointLineAnim);
	}
}
