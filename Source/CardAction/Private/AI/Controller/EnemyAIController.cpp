// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/EnemyAIController.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }
}