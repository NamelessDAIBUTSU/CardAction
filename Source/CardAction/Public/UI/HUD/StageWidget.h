// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include "Map/Stage/StageObject.h"
#include <UI/StageArrowWidget.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "StageWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageWidget : public UHUDBase
{
	GENERATED_BODY()
	
protected: /* UUserWidget */
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public: /* マウスイベント */
	UFUNCTION()
	void OnClicked();
	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

public:
	void PlayConditionAnim();

	void SetStageObject(UStageObject* S) { Stage = S; }
	UStageObject* GetStageObject() const { return Stage; }

	// エンジンから独立した更新クラス
	virtual void OnUpdate(float DeltaSec) override;
	
private: /* アニメーション */
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Clear;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* NotSelect;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* CanSelect;

private:
	// ステージオブジェクト
	UStageObject* Stage = nullptr;

	// 矢印ウィジェット
	UPROPERTY(meta = (BindWidget))
	UStageArrowWidget* ArrowWidget = nullptr;

	// ボタン
	UPROPERTY(meta = (BindWidget))
	UButton* StageButton = nullptr;
};
