// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanMove.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UBTDecorator_CanMove : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CanMove();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
