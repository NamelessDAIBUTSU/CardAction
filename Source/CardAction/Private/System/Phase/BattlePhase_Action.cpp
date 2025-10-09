// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Action.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

// �t�F�[�Y��
void UBattlePhase_Action::OnTick(float DeltaSec)
{
	// �G���S�ł��Ă�����t�F�[�Y��؂�ւ��t���O�𗧂Ă�
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
	{
		AGridManager* GridManager = MyGameMode->GridManager;
		if (GridManager == nullptr)
			return;

		bRequestChangePhase = (GridManager->IsExistEnemyOnGrid() == false);
	}
}
