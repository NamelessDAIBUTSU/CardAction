// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Entry.h"
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Enemy/EnemyManager.h"

void UBattlePhase_Entry::OnTick(float DeltaSec)
{
	// �G�X�e�[�W����Ȃ��ꍇ�͂����ɃA�N�V�����t�F�[�Y�փ��N�G�X�g
	if (false)
	{
		RequestNextPhase = EBattlePhase::Action;
		return;
	}

	// �O���b�h��ɂ���S�G���G���g���[���[�V�������s������J�[�h�I���t�F�[�Y�փ��N�G�X�g
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->EnemyManager && MyGM->EnemyManager->IsAllEnemyReady())
		{
			RequestNextPhase = EBattlePhase::CardSelect;
			return;
		}
	}
}
