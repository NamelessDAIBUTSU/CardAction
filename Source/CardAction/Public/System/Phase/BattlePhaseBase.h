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
	// �t�F�[�Y�J�n��
	virtual void OnBegin() {}
	// �t�F�[�Y��
	virtual void OnTick(float DeltaSec) {}
	// �t�F�[�Y�I����
	virtual void OnExit() {}

public:
	EBattlePhase GetBattlePhase() const { return BattlePhase; }
	EBattlePhase GetRequestNextPhase() const { return RequestNextPhase; }

	bool IsRequestChangePhase() const { return RequestNextPhase != EBattlePhase::None; }

protected:
	EBattlePhase BattlePhase;

	// �؂�ւ������t�F�[�Y
	EBattlePhase RequestNextPhase = EBattlePhase::None;
};
