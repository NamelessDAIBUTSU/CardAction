// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CharaBannerWidget.h"
#include "Enemy/EnemyBase.h"

void UCharaBannerWidget::Setup(AEnemyBase* Enemy)
{
	if (Enemy == nullptr)
		return;

	// �A�C�R���ݒ�
	if (IconImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Enemy->IconTexture);
		IconImage->SetBrush(Brush);
	}

	// ���O�ݒ�
	if (EnemyNameText)
	{
		EnemyNameText->SetText(FText::FromName(Enemy->Name));
	}

	// ���C�A�E�g�ݒ�
	ChangeLayout(false);
}

// �������C�A�E�g�ύX
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
