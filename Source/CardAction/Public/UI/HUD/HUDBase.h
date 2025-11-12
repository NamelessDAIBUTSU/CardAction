// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDBase.generated.h"

/**
 * 
 */
UCLASS(abstract)
class CARDACTION_API UHUDBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void PlayInAnim();
	virtual void PlayOutAnim();

	bool IsPlayingInAnim();
	bool IsPlayingOutAnim();

	// エンジンから独立した更新クラス
	virtual void OnUpdate(float DeltaSec) {}

	// アクションフェーズ以外でも表示するか
	virtual bool IsVisibleExceptActionPhase() { return true; }

protected:
	// アニメーション
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* InAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OutAnim;
};
