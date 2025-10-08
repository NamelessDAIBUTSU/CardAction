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
	// �t�F�[�Y�J�n��
	virtual void OnBegin() {}
	// �t�F�[�Y��
	virtual void OnTick(float DeltaSec) {}
	// �t�F�[�Y�I����
	virtual void OnExit() {}

public:
	EBattlePhase GetBattlePhase() const { return BattlePhase; }

	bool IsRequestChangePhase() const { return bRequestChangePhase; }

protected:
	EBattlePhase BattlePhase;

	// �t�F�[�Y��؂�ւ��邩
	bool bRequestChangePhase = false;
};
