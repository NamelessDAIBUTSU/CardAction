// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageClearWidget.h"
#include <Kismet/GameplayStatics.h>
#include <System/FadeSystem.h>

bool UStageClearWidget::Initialize()
{
	if (Super::Initialize() == false)
		return false;

	// 決定時のコールバック登録
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

        // バインド解除
        UnbindAllFromAnimationFinished(OutAnim);

        // Outアニメーションを再生
        StopAnimation(OutAnim);
        PlayAnimation(OutAnim);

        // アニメーション終了時のコールバック登録
        FWidgetAnimationDynamicEvent Delegate;
        Delegate.BindUFunction(this, FName("OnFinishOutAnim"));
        BindToAnimationFinished(OutAnim, Delegate);
    }
}

// アニメーション終了時のコールバック
void UStageClearWidget::OnFinishOutAnim()
{
    if (GetGameInstance() == nullptr)
        return;

    UFadeSystem* FadeSystem = GetGameInstance()->GetSubsystem<UFadeSystem>();
    if (FadeSystem == nullptr)
        return;

    FadeSystem->FadeOutAndOpenLevel(FName("StageSelectLevel"));
}