// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardEffectBase.generated.h"

/// <summary>
/// カード効果の基本クラス
/// </summary>
UCLASS(Blueprintable, Abstract)
class CARDACTION_API UCardEffectBase : public UObject
{
	GENERATED_BODY()
	
public:
	// 効果発動
	virtual void ExecuteEffect() PURE_VIRTUAL(ExecuteEffect, );
};
