// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <System/Phase/BattlePhaseDef.h>
#include "BattlePhaseDef.h"
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
	EBattlePhase GetRequestNextPhase() const { return RequestNextPhase; }

	bool IsRequestChangePhase() const { return RequestNextPhase != EBattlePhase::None; }

protected:
	EBattlePhase BattlePhase;

	// 切り替えたいフェーズ
	EBattlePhase RequestNextPhase = EBattlePhase::None;
};
