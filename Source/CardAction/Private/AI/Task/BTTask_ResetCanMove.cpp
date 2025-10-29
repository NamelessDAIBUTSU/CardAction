// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_ResetCanMove.h"
#include <Enemy/EnemyBase.h>
#include "AIController.h"

EBTNodeResult::Type UBTTask_ResetCanMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());
	if (Enemy == nullptr)
		return EBTNodeResult::Failed;

	// カウントをリセット
	Enemy->SetMoveCount(0);

	// 移動可能フラグを立てる
	Enemy->SetCanMove(true);

	return EBTNodeResult::Succeeded;
}