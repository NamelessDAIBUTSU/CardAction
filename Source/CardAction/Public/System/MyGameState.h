// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include <System/Phase/BattlePhaseDef.h>
#include "MyGameState.generated.h"

UCLASS()
class CARDACTION_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	EBattlePhase GetCurrentBattlePhase() const { return CurrentBattlePhase; }

private:
	// 現在のバトルフェーズ
	EBattlePhase CurrentBattlePhase;
};
