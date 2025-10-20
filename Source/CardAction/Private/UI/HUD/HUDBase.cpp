// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HUDBase.h"

void UHUDBase::PlayInAnimation()
{
    if (InAnim)
    {
        PlayAnimation(InAnim);
    }
}

void UHUDBase::PlayOutAnimation()
{
    if (OutAnim)
    {
        PlayAnimation(OutAnim);
    }
}