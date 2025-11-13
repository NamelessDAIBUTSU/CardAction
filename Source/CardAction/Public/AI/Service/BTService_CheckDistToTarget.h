// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckDistToTarget.generated.h"

/// <summary>
/// サービス：ターゲットアクターとの距離によって攻撃可能か判定する
/// </summary>
UCLASS()
class CARDACTION_API UBTService_CheckDistToTarget : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
