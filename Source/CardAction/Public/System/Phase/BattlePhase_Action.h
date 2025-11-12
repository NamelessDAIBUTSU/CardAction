// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Phase/BattlePhaseBase.h"
#include "BattlePhase_Action.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UBattlePhase_Action : public UBattlePhaseBase
{
	GENERATED_BODY()
	
public:
	UBattlePhase_Action() { BattlePhase = EBattlePhase::Action; }

public: /* UBattlePhaseBase */
	// フェーズ開始時
	virtual void OnBegin() override;
	// フェーズ中
	virtual void OnTick(float DeltaSec) override;
	// フェーズ終了時
	virtual void OnExit() override;

public:
	// 残り時間を整数で取得
	int GetCurrentRemainSec();

private:
	float PhaseEndSec = 30.f;
	float ElapsedSec = 0.f;
};
