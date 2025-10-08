// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Service/BTService_UpdateTargetActor.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include <Character/MyCharacter.h>

void UBTService_UpdateTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* EnemyController = OwnerComp.GetAIOwner();
	if (EnemyController == nullptr)
		return;

	UBlackboardComponent* BBComp = EnemyController->GetBlackboardComponent();
	if (BBComp)
	{
		BBComp->SetValueAsObject("TargetActor", UGameplayStatics::GetPlayerCharacter(EnemyController->GetWorld(), 0));
	}
}
