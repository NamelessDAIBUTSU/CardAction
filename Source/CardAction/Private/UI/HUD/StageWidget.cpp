// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageWidget.h"
#include <System/FadeSystem.h>
#include <Map/MapManager.h>

void UStageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StageButton)
	{
		StageButton->IsFocusable = false;
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

	if (GetWorld()->GetGameInstance() == nullptr)
		return;

	UFadeSystem* FadeSystem = GetWorld()->GetGameInstance()->GetSubsystem<UFadeSystem>();
	if (FadeSystem == nullptr)
		return;

	UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr)
		return;

	// ���݂̃X�e�[�W�̍X�V
	if (UMapObject* CurrentMap = MapManager->GetCurrentMap())
		CurrentMap->SetCurrentStage(Stage);

	// �I�������X�e�[�W�ւ̑J�ڏ���
	FadeSystem->FadeOutAndOpenLevel(MapManager->GetCurrentLevelName());
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