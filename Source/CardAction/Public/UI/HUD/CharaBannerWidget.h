// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "CharaBannerWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCharaBannerWidget : public UHUDBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override {}

public:
	// ウィジェットの設定
	void Setup(class AEnemyBase* Enemy);

	// 生死レイアウト変更
	void ChangeLayout(bool IsDead);
	
private:
	// 生死レイアウトアニメーション
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* AliveLayoutAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DeadLayoutAnim;

	// アイコンイメージウィジェット
	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	// 敵の名前テキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyNameText;
};
