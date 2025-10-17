// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include "StageClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UStageClearWidget : public UHUDBase
{
	GENERATED_BODY()

public: /* UHUDBase */
	virtual void PlayInAnimation() override;
	virtual void PlayOutAnimation() override;

	virtual void OnUpdate(float DeltaSec) override {}
};
