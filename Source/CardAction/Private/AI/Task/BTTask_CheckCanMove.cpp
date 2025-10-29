// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_CheckCanMove.h"
#include <Enemy/EnemyBase.h>
#include "AIController.h"

EBTNodeResult::Type UBTTask_CheckCanMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());
	if (Enemy == nullptr)
		return EBTNodeResult::Failed;

	if (Enemy->GetMoveCount() >= Enemy->AttackSpan)
	{
		// ˆÚ“®‰Â”\ƒtƒ‰ƒO‚ð~‚ë‚·
		Enemy->SetCanMove(false);
	}

	return EBTNodeResult::Succeeded;
}