// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CharaBannerWidget.h"
#include "Enemy/EnemyBase.h"

void UCharaBannerWidget::Setup(AEnemyBase* Enemy)
{
	if (Enemy == nullptr)
		return;

	// アイコン設定
	if (IconImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Enemy->IconTexture);
		IconImage->SetBrush(Brush);
	}

	// 名前設定
	if (EnemyNameText)
	{
		EnemyNameText->SetText(FText::FromName(Enemy->Name));
	}

	// レイアウト設定
	ChangeLayout(false);
}

// 生死レイアウト変更
void UCharaBannerWidget::ChangeLayout(bool IsDead)
{
	if (IsDead && DeadLayoutAnim)
	{
		PlayAnimation(DeadLayoutAnim);
	}
	if (IsDead == false && AliveLayoutAnim)
	{
		PlayAnimation(AliveLayoutAnim);
	}
}
