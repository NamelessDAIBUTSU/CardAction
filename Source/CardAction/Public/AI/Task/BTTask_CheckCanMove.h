// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckCanMove.generated.h"

/// <summary>
/// タスク：グリッド移動の回数でシーケンス切り替え用のBool値を更新する
/// </summary>
UCLASS()
class CARDACTION_API UBTTask_CheckCanMove : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
