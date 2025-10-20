// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/StageClearWidget.h"
#include <Kismet/GameplayStatics.h>

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
    // フェードリクエスト
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC && PC->PlayerCameraManager)
    {
        PC->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, 1.0f, FLinearColor::Black, false, true);
    }
}