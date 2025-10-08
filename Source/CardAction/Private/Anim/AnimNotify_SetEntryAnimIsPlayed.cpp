// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/AnimNotify_SetEntryAnimIsPlayed.h"
#include <Enemy/EnemyBase.h>

void UAnimNotify_SetEntryAnimIsPlayed::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp == nullptr)
        return;

    AActor* Owner = MeshComp->GetOwner();
    if (AEnemyBase* Enemy = Cast<AEnemyBase>(Owner))
    {
        Enemy->bIsPlayedEntryAnim = true;
    }
}