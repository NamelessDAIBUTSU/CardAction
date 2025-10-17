// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Result.h"
#include <Character/MyPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "UI/HUD/StageClearWidget.h"


// �t�F�[�Y�J�n��
void UBattlePhase_Result::OnBegin()
{
	// �X�e�[�W�N���A�E�B�W�F�b�g�̕\���ƃA�j���[�V����
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UStageClearWidget* StageClearWidget = PlayerController->MainHUDWidget->StageClearWidget;
	if (StageClearWidget == nullptr)
		return;

	StageClearWidget->SetVisibility(ESlateVisibility::Visible);
	StageClearWidget->PlayInAnimation();
}

void UBattlePhase_Result::OnTick(float DeltaSec)
{
}

void UBattlePhase_Result::OnExit()
{
	// �X�e�[�W�N���A�E�B�W�F�b�g�̔�\���ƃA�j���[�V����
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UStageClearWidget* StageClearWidget = PlayerController->MainHUDWidget->StageClearWidget;
	if (StageClearWidget == nullptr)
		return;

	StageClearWidget->PlayOutAnimation();
}
