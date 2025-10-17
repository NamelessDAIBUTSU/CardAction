// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/AnimNotify_SetIsReady.h"
#include <Enemy/EnemyBase.h>

void UAnimNotify_SetIsReady::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp == nullptr)
        return;

    AActor* Owner = MeshComp->GetOwner();
    if (AEnemyBase* Enemy = Cast<AEnemyBase>(Owner))
    {
        Enemy->SetIsReady(true);
    }
}