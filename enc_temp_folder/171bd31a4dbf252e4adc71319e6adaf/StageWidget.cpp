// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageWidget.h"

void UStageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StageButton)
	{
		StageButton->OnClicked.AddDynamic(this, &UStageWidget::OnClicked);
	}
}

void UStageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StageButton)
	{
		StageButton->IsFocusable = false;
	}
}

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


void UStageWidget::OnClicked()
{
	// �I���\����Ȃ��ꍇ�͉����������Ȃ�
	if (Stage == nullptr || Stage->GetStageCondition() != EStageCondition::CanSelect)
		return;

	// �I�������X�e�[�W�ւ̑J�ڏ���

}

void UStageWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// �I���\����Ȃ��ꍇ�͉����������Ȃ�
	if (Stage == nullptr || Stage->GetStageCondition() != EStageCondition::CanSelect)
		return;

	// ���A�C�R���̕\���A�j���[�V����
	if (ArrowWidget)
	{
		ArrowWidget->PlayIdleAnim();
	}
}

void UStageWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	// �I���\����Ȃ��ꍇ�͉����������Ȃ�
	if (Stage == nullptr || Stage->GetStageCondition() != EStageCondition::CanSelect)
		return;

	// ���A�C�R���̔�\���A�j���[�V����
	if (ArrowWidget)
	{
		ArrowWidget->PlayHideAnim();
	}
}