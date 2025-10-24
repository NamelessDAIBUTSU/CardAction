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
	// 選択可能じゃない場合は何も処理しない
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

	// 現在のステージの更新
	if (UMapObject* CurrentMap = MapManager->GetCurrentMap())
		CurrentMap->SetCurrentStage(Stage);

	// 選択したステージへの遷移処理
	FadeSystem->FadeOutAndOpenLevel(MapManager->GetCurrentLevelName());
}

void UStageWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 選択可能じゃない場合は何も処理しない
	if (Stage == nullptr || Stage->GetStageCondition() != EStageCondition::CanSelect)
		return;

	// 矢印アイコンの表示アニメーション
	if (ArrowWidget)
	{
		ArrowWidget->PlayIdleAnim();
	}
}

void UStageWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	// 選択可能じゃない場合は何も処理しない
	if (Stage == nullptr || Stage->GetStageCondition() != EStageCondition::CanSelect)
		return;

	// 矢印アイコンの非表示アニメーション
	if (ArrowWidget)
	{
		ArrowWidget->PlayHideAnim();
	}
}