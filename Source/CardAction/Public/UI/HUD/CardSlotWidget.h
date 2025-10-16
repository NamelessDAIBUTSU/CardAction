// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/SizeBox.h>
#include <Components/TextBlock.h>
#include "CardSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 初期化
	virtual void NativeConstruct() override;

public:
	// スロットにカードを設定
	void SetupCardSlot(class UCardData* Data);

	// カード選択アニメーション再生
	void PlaySelectAnim();
	// カード選択解除アニメーション再生
	void PlayUnSelectAnim();

	// 効果発動
	void ExecuteEffect();

	// カードウィジェットのアニメーションをデフォルトに戻す
	void PlayDefaultAnimation();

public:
	// カードクラス
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CardWidgetClass;

	// カードウィジェット
	class UCardWidget* CardWidget;

	// 配置用サイズボックス
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox;

	// アニメーション
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SelectAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* UnSelectAnim;

	bool bIsSelected = false;
};
