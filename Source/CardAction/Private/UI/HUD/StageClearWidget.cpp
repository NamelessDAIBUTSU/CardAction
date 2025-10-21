// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageClearWidget.h"
#include <Kismet/GameplayStatics.h>
#include <System/FadeSystem.h>

bool UStageClearWidget::Initialize()
{
	if (Super::Initialize() == false)
		return false;

	// ���莞�̃R�[���o�b�N�o�^
	if (DecideButton)
	{
		DecideButton->OnClicked.AddDynamic(this, &UStageClearWidget::OnDecide);
	}

    return true;
}

void UStageClearWidget::PlayInAnimation()
{
	PlayAnimation(InAnim);
}


void UStageClearWidget::PlayOutAnimation()
{
	PlayAnimation(OutAnim);
}

void UStageClearWidget::OnDecide()
{
    if (OutAnim)
    {
        bIsPlayingOutAnim = true;

        // �o�C���h����
        UnbindAllFromAnimationFinished(OutAnim);

        // Out�A�j���[�V�������Đ�
        StopAnimation(OutAnim);
        PlayAnimation(OutAnim);

        // �A�j���[�V�����I�����̃R�[���o�b�N�o�^
        FWidgetAnimationDynamicEvent Delegate;
        Delegate.BindUFunction(this, FName("OnFinishOutAnim"));
        BindToAnimationFinished(OutAnim, Delegate);
    }
}

// �A�j���[�V�����I�����̃R�[���o�b�N
void UStageClearWidget::OnFinishOutAnim()
{
    if (GetGameInstance() == nullptr)
        return;

    UFadeSystem* FadeSystem = GetGameInstance()->GetSubsystem<UFadeSystem>();
    if (FadeSystem == nullptr)
        return;

    FadeSystem->FadeOutAndOpenLevel(FName("StageSelectLevel"));
}