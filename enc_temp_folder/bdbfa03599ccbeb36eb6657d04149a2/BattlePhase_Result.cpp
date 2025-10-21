// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Phase/BattlePhase_Result.h"
#include <Character/MyPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "UI/HUD/StageClearWidget.h"
#include <System/FadeSystem.h>


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
	StageClearWidget->PlayInAnim();
}

void UBattlePhase_Result::OnTick(float DeltaSec)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UStageClearWidget* StageClearWidget = PlayerController->MainHUDWidget->StageClearWidget;
	if (StageClearWidget == nullptr)
		return;

	// �X�e�[�W�N���A�E�B�W�F�b�g��OutAnim���I��������X�e�[�W�I�����x���Ɉړ�����
	if (StageClearWidget->IsOutAnimFinished())
	{
		RequestNextPhase = EBattlePhase::End;
	}
}

// �t�F�[�h�A�E�g���ăX�e�[�W�I�����x���ɑJ��
void UBattlePhase_Result::OnExit()
{
	if (GetWorld()->GetGameInstance() == nullptr)
		return;

	UFadeSystem* FadeSystem = GetWorld()->GetGameInstance()->GetSubsystem<UFadeSystem>();
	if (FadeSystem == nullptr)
		return;

	FadeSystem->FadeOutAndOpenLevel(FName("ActionMap"));
}
