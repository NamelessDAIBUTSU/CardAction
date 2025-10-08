// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitSec.generated.h"

USTRUCT()
struct FWaitTaskMemory
{
    GENERATED_BODY()

public:
    FTimerHandle TimerHandle;
};

UCLASS()
class CARDACTION_API UBTTask_WaitSec : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    // NodeMemory ‚ÌƒTƒCƒY‚ð•Ô‚·
    virtual uint16 GetInstanceMemorySize() const override { return sizeof(FWaitTaskMemory); }

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UFUNCTION()
    void OnWaitFinished();

public:
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector WaitTimeKey;

private:
    UBehaviorTreeComponent* OwnerCompPtr = nullptr;
};
