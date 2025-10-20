// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Action.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include <Grid/GridManager.h>
#include <Character/MyPlayerController.h>


// �t�F�[�Y�J�n��
void UBattlePhase_Action::OnBegin() 
{ 
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;

	// �A�N�V�����t�F�[�Y�ȊO�Ŕ�\���ɂ���E�B�W�F�b�g��\��
	PlayerController->MainHUDWidget->SetVisibleExceptActionPhase(true);
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

void UBattlePhase_Action::OnExit()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;

	// �A�N�V�����t�F�[�Y�ȊO�Ŕ�\���ɂ���E�B�W�F�b�g������
	PlayerController->MainHUDWidget->SetVisibleExceptActionPhase(false);
}
