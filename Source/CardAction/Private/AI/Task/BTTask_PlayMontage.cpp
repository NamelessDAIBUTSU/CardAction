// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_PlayMontage.h"
#include "GameFramework/Character.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;
	ACharacter* Owner = Cast<ACharacter>(AIController->GetPawn());
	if (Owner == nullptr)
		return EBTNodeResult::Failed;
	auto* Mesh = Owner->GetMesh();
	if (Mesh == nullptr)
		return EBTNodeResult::Failed;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (AnimInstance && AnimMontage)
	{
		// モンタージュ再生
		AnimInstance->Montage_Play(AnimMontage, PlayRate);

		// 終了コールバックをバインド
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UBTTask_PlayMontage::OnMontageEnded, &OwnerComp);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, AnimMontage);

		// まだ完了していないので InProgress を返す
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

// モンタージュ終了時にSucceededを返すためのコールバック
void UBTTask_PlayMontage::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp)
	{
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}