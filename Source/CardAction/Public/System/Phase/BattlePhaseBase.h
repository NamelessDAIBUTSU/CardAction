// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <System/Phase/BattlePhaseDef.h>
#include "BattlePhaseBase.generated.h"


UCLASS(abstract)
class CARDACTION_API UBattlePhaseBase : public UObject
{
	GENERATED_BODY()
	
public:
	// フェーズ開始時
	virtual void OnBegin() {}
	// フェーズ中
	virtual void OnTick(float DeltaSec) {}
	// フェーズ終了時
	virtual void OnExit() {}

public:
	EBattlePhase GetBattlePhase() const { return BattlePhase; }

	bool IsRequestChangePhase() const { return bRequestChangePhase; }

protected:
	EBattlePhase BattlePhase;

	// フェーズを切り替えるか
	bool bRequestChangePhase = false;
};
