// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Util/CoordDef.h"
#include "BTTask_GridMove.generated.h"

 /// <summary>
 /// タスク：周囲のどこかへ1マス移動
 /// </summary>
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
	// 何秒で移動するか
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GoalSec = 1.f;

	// 斜め移動を許すか
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanMoveDiagonal = false;

private:
	FCoord TargetCoord = FCoord::Zero();
};

