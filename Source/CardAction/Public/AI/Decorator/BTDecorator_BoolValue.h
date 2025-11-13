// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTDecorator_BoolValue.generated.h"

/// <summary>
/// デコレーター：ブラックボードのBool値を見て評価する
/// </summary>
UCLASS()
class CARDACTION_API UBTDecorator_BoolValue : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_BoolValue();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BoolKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool Value;
};
