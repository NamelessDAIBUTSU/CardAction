// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_SetRandomFloat.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetRandomFloat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return EBTNodeResult::Failed;

	float Min = BBComp->GetValueAsFloat(MinFloatKey.SelectedKeyName);
	float Max = BBComp->GetValueAsFloat(MaxFloatKey.SelectedKeyName);
	float RandNum = FMath::FRandRange(Min, Max);

	BBComp->SetValueAsFloat(SetFloatKey.SelectedKeyName, RandNum);

	return EBTNodeResult::Succeeded;
}