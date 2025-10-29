// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MoveCountUp.h"

#include "AIController.h"
#include <Enemy/EnemyBase.h>
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Grid/GridManager.h"

EBTNodeResult::Type UBTTask_MoveCountUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());
	if (Enemy == nullptr)
		return EBTNodeResult::Failed;

	int NextCount = Enemy->GetMoveCount() + 1;
	Enemy->SetMoveCount(NextCount);

	return EBTNodeResult::Succeeded;
}