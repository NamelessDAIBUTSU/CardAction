// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UBTTask_PlayMontage : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp);

public:
	// �����^�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* AnimMontage = nullptr;
	// �Đ����x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	float PlayRate = 1.f;
};
