// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_CheckDistToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include <Character/MyCharacter.h>

void UBTService_CheckDistToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* EnemyController = OwnerComp.GetAIOwner();
	if (EnemyController == nullptr)
		return;

	APawn* Pawn = EnemyController->GetPawn();
	if (Pawn == nullptr)
		return;

	UBlackboardComponent* BBComp = EnemyController->GetBlackboardComponent();
	if (BBComp == nullptr)
		return;

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
	if (TargetActor == nullptr)
		return;

	// プレイヤーとエネミー（自身）の距離が指定距離内に入ったかチェック
	float Distance = FMath::Abs(FVector::Dist(TargetActor->GetActorLocation(), Pawn->GetActorLocation()));
	float BBDistance = BBComp->GetValueAsFloat("DistanceToTarget");

	BBComp->SetValueAsBool("CanAttack", BBDistance >= Distance);

	// 指定範囲内の場合、ターゲットアクターを空にする
	UObject* NewTargetActor = BBDistance >= Distance ? nullptr : Cast<UObject>(UGameplayStatics::GetPlayerCharacter(EnemyController->GetWorld(), 0));
	BBComp->SetValueAsObject("TargetObject", NewTargetActor);
}
