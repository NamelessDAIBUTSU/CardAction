// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSelectWidget.h"
#include "Animation/WidgetAnimationEvents.h"

	// ������
bool UCardSelectWidget::Initialize()
{
    if (Super::Initialize() == false)
        return false;

    // ���莞�̃R�[���o�b�N�o�^
    if (DecideButton)
    {
        DecideButton->OnClicked.AddDynamic(this, &UCardSelectWidget::OnDecide);
    }

    // Hidden��Visible�ɕς�����Ƃ��Ƀt���O������������
    OnVisibilityChanged.AddDynamic(this, &UCardSelectWidget::OnChangeVisibility);

    return true;
}

void UCardSelectWidget::OnDecide()
{
    if (OutAnim)
    {
        bIsPlayingOutAnim = true;

        // �o�C���h����
        UnbindAllFromAnimationFinished(OutAnim);

        // Out�A�j���[�V�������Đ�
        StopAnimation(OutAnim); 
        PlayAnimation(OutAnim);

        // �A�j���[�V�����I�����Ɋm��t���O�𗧂Ă�悤�R�[���o�b�N�o�^
        FWidgetAnimationDynamicEvent Delegate;
        Delegate.BindUFunction(this, FName("OnChangeIsDecided"));
        BindToAnimationFinished(OutAnim, Delegate);

        UE_LOG(LogTemp, Warning, TEXT("OnDecide"));
    }
}

// �r�W�u���ύX���̃R�[���o�b�N
void UCardSelectWidget::OnChangeVisibility(ESlateVisibility NextVisibility)
{
    if (NextVisibility == ESlateVisibility::Visible)
    {
        bIsDecided = false;
    }
}

void UCardSelectWidget::OnChangeIsDecided()
{
    if (bIsPlayingOutAnim == false)
        return;

    UE_LOG(LogTemp, Warning, TEXT("OnChangeIsDecided"));
    bIsDecided = true;
    bIsPlayingOutAnim = false;
}

void UCardSelectWidget::PlayInAnimation()
{
    if (InAnim)
    {
        StopAnimation(InAnim);
        PlayAnimation(InAnim);
    }
}
