// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateTargetActor.generated.h"

/// <summary>
/// サービス：ターゲットアクター（プレイヤー）変数を更新する
/// </summary>
UCLASS()
class CARDACTION_API UBTService_UpdateTargetActor : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
