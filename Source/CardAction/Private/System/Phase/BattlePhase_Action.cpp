// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Action.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include <Grid/GridManager.h>


// �t�F�[�Y�J�n��
void UBattlePhase_Action::OnBegin() 
{ 
	UE_LOG(LogTemp, Warning, TEXT("Begin ActionPhase"));
}

// �t�F�[�Y��
void UBattlePhase_Action::OnTick(float DeltaSec)
{
	if (RequestNextPhase != EBattlePhase::None)
		return;

	// �t�F�[�Y�؂�ւ�����
	// ���ԂŃJ�[�h�I����
	ElapsedSec += DeltaSec;
	if (ElapsedSec >= PhaseEndSec)
	{
		RequestNextPhase = EBattlePhase::CardSelect;
		return;
	}

	// �G�r�łŃ��U���g��
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
	{
		AGridManager* GridManager = MyGameMode->GridManager;
		if (GridManager == nullptr)
			return;

		// �G���S�ł��Ă�����A���U���g�t�F�[�Y�ւ̐؂�ւ����N�G�X�g
		if (GridManager->IsExistEnemyOnGrid() == false)
		{
			RequestNextPhase = EBattlePhase::Result;
			return;
		}
	}
}
