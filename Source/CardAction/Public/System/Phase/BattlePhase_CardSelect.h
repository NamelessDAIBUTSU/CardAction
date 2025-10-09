// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Phase/BattlePhaseBase.h"
#include "BattlePhase_CardSelect.generated.h"

/**
 *
 */
UCLASS()
class CARDACTION_API UBattlePhase_CardSelect : public UBattlePhaseBase
{
	GENERATED_BODY()

public:
	UBattlePhase_CardSelect() { BattlePhase = EBattlePhase::CardSelect; }

public: /* UBattlePhaseBase */
	// フェーズ開始時
	virtual void OnBegin() override {}
	// フェーズ中
	virtual void OnTick(float DeltaSec) override;
	// フェーズ終了時
	virtual void OnExit() override {}

};
