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
	// スロット番号の設定
	void SetupSlotNum(int Num);
	// スロットにカードを設定
	void SetupCardSlot(class UCardData* Data);

	// カード選択アニメーション再生
	void PlaySelectAnim();
	// カード選択解除アニメーション再生
	void PlayUnSelectAnim();

	// 効果発動
	void ExecuteEffect();

public:
	// カードクラス
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CardWidgetClass;

	// カードウィジェット
	class UCardWidget* CardWidget;

	// 配置用サイズボックス
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox;

	// スロットナンバーテキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotNum;

	// アニメーション
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SelectAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* UnSelectAnim;

	bool bIsSelected = false;
};
