// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/Phase/BattlePhaseBase.h"
#include "BattlePhase_Result.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UBattlePhase_Result : public UBattlePhaseBase
{
	GENERATED_BODY()

public:
	UBattlePhase_Result() { BattlePhase = EBattlePhase::Result; }

public: /* UBattlePhaseBase */
	// �t�F�[�Y�J�n��
	virtual void OnBegin() override;
	// �t�F�[�Y��
	virtual void OnTick(float DeltaSec) override;
	// �t�F�[�Y�I����
	virtual void OnExit() override;

};
