// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_BoolValue.h"

UBTDecorator_BoolValue::UBTDecorator_BoolValue()
{
	bNotifyTick = true;               // TickNode ���Ă�ł��炤
	bAllowAbortChildNodes = true;     // �������ς������q�m�[�h�𒆒f
}

bool UBTDecorator_BoolValue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return false;

	return BBComp->GetValueAsBool(BoolKey.SelectedKeyName) == Value;
}

void UBTDecorator_BoolValue::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// ���t���[���������`�F�b�N���ď����ω��������BT���ĕ]��
	bool bResult = CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (bResult == false)
	{
		OwnerComp.RequestExecution(this); 
	}
}