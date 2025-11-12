// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/Button.h>
#include "StageClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageClearWidget : public UHUDBase
{
	GENERATED_BODY()

public:
	// 初期化
	virtual bool Initialize() override;

public: /* UHUDBase */
	virtual void PlayInAnim() override;
	virtual void PlayOutAnim() override;

	virtual void OnUpdate(float DeltaSec) override {}

public:
	// 決定ボタン押下時のコールバック
	UFUNCTION()
	void OnDecide();

	// アニメーション終了時のコールバック
	UFUNCTION()
	void OnFinishOutAnim();

	// アウトアニメが終了したか
	bool IsOutAnimFinished() const { return bIsOutAnimFinished; }

private:
	// 決定ボタン
	UPROPERTY(meta = (BindWidget))
	UButton* DecideButton;

	// 遷移用フラグ
	bool bIsOutAnimFinished = false;
};
