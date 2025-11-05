// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GridMove.generated.h"

/**
 * ŽüˆÍ‚Ì‚Ç‚±‚©‚Ö1ƒ}ƒXˆÚ“®
 */
UCLASS()
class CARDACTION_API UBTTask_GridMove : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GridMove();

public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	// ‰½•b‚ÅˆÚ“®‚·‚é‚©
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GoalSec = 1.f;

	// ŽÎ‚ßˆÚ“®‚ð‹–‚·‚©
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanMoveDiagonal = false;

private:
	FVector2D TargetCoord = FVector2D::Zero();
};

