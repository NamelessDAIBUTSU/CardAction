// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HUDBase.h"

void UHUDBase::PlayInAnim()
{
    if (InAnim)
    {
        PlayAnimation(InAnim);
    }
}

void UHUDBase::PlayOutAnim()
{
    if (OutAnim)
    {
        PlayAnimation(OutAnim);
    }
}

bool UHUDBase::IsPlayingInAnim()
{
   return IsAnimationPlaying(InAnim);
}

bool UHUDBase::IsPlayingOutAnim()
{
    return IsAnimationPlaying(OutAnim);
}
