// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSelectWidget.h"
#include "Animation/WidgetAnimationEvents.h"

	// 初期化
bool UCardSelectWidget::Initialize()
{
    if (Super::Initialize() == false)
        return false;

    // 決定時のコールバック登録
    if (DecideButton)
    {
        DecideButton->OnClicked.AddDynamic(this, &UCardSelectWidget::OnDecide);
    }

    // Hidden→Visibleに変わったときにフラグを初期化する
    OnVisibilityChanged.AddDynamic(this, &UCardSelectWidget::OnChangeVisibility);

    return true;
}

void UCardSelectWidget::OnDecide()
{
    if (OutAnim)
    {
        bIsPlayingOutAnim = true;

        // バインド解除
        UnbindAllFromAnimationFinished(OutAnim);

        // Outアニメーションを再生
        StopAnimation(OutAnim); 
        PlayAnimation(OutAnim);

        // アニメーション終了時に確定フラグを立てるようコールバック登録
        FWidgetAnimationDynamicEvent Delegate;
        Delegate.BindUFunction(this, FName("OnChangeIsDecided"));
        BindToAnimationFinished(OutAnim, Delegate);

        UE_LOG(LogTemp, Warning, TEXT("OnDecide"));
    }
}

// ビジブル変更時のコールバック
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
