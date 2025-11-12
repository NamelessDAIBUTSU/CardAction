// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_CanMove.h"
#include <Enemy/EnemyBase.h>
#include "AIController.h"

UBTDecorator_CanMove::UBTDecorator_CanMove()
{
	// TickNode を呼んでもらう
	bNotifyTick = true;
	// 条件が変わったら子ノードを中断
	//bAllowAbortChildNodes = true;
}

void UBTDecorator_CanMove::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return;

	AEnemyBase* Owner = Cast<AEnemyBase>(AIController->GetPawn());
	if (Owner == nullptr)
		return;
}

bool UBTDecorator_CanMove::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return false;

	AEnemyBase* Owner = Cast<AEnemyBase>(AIController->GetPawn());
	if (Owner == nullptr)
		return false;

	return Owner->CanMove();
}
