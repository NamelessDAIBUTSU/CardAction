// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "CardSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 初期化
	virtual bool Initialize() override;

public:
	// 決定時のコールバック
	UFUNCTION()
	void OnDecide();

	// ビジブル変更時のコールバック
	UFUNCTION()
	void OnChangeVisibility(ESlateVisibility NextVisibility);
	UFUNCTION()
	void OnChangeIsDecided();

	// アクションフェーズへの遷移判定
	bool GetIsDecided() const { return bIsDecided; }

	// Inアニメーションの再生
	void PlayInAnimation();

public:
	// アニメーション
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* InAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OutAnim;

	// 決定ボタン
	UPROPERTY(meta = (BindWidget))
	UButton* DecideButton;

private:
	// 確定させたか
	bool bIsDecided = false;
	// Outアニメーション中か
	bool bIsPlayingOutAnim = false;
};
