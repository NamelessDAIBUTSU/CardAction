// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardEffectBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class CARDACTION_API UCardEffectBase : public UObject
{
	GENERATED_BODY()
	
public:
	// Œø‰Ê”­“®
	virtual void ExecuteEffect() PURE_VIRTUAL(ExecuteEffect, );
};
