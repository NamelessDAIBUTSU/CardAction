// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_WaitSec.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_WaitSec::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    FWaitTaskMemory* MyMemory = reinterpret_cast<FWaitTaskMemory*>(NodeMemory);

    if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
    {
        float WaitTime = BB->GetValueAsFloat(WaitTimeKey.SelectedKeyName);
        UWorld* World = OwnerComp.GetWorld();
        if (World)
        {
            FTimerDelegate TimerDel;
            TimerDel.BindLambda([this, &OwnerComp, MyMemory]()
                {
                    this->FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                });

            World->GetTimerManager().SetTimer(MyMemory->TimerHandle, TimerDel, WaitTime, false);
            return EBTNodeResult::InProgress;
        }
    }

    return EBTNodeResult::Failed;
}

void UBTTask_WaitSec::OnWaitFinished()
{
    if (UBlackboardComponent* BBComp = OwnerCompPtr->GetBlackboardComponent())
    {
        float WaitTime = BBComp->GetValueAsFloat(WaitTimeKey.SelectedKeyName);
        UE_LOG(LogTemp, Warning, TEXT("Finished(%f Sec)"), WaitTime);
    }

    if (OwnerCompPtr)
    {
        FinishLatentTask(*OwnerCompPtr, EBTNodeResult::Succeeded);
    }
}
