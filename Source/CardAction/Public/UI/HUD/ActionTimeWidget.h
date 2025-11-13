// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/TextBlock.h>
#include "ActionTimeWidget.generated.h"

/// <summary>
/// ウィジェット：アクションフェーズの制限時間
/// </summary>
UCLASS()
class CARDACTION_API UActionTimeWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	virtual void OnUpdate(float DeltaSec) override;

	// アクションフェーズ以外で非表示
	virtual bool IsVisibleExceptActionPhase() override{ return false; }

private:
	UPROPERTY(meta =(BindWidget))
	UTextBlock* RemainTimeText = nullptr;
};
