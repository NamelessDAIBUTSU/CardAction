// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_EnemyAttack.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return EBTNodeResult::Failed;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (AnimInstance && AnimMontage)
	{
		// �v���C���[�Ɍ������ĉ�]
		AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
			return EBTNodeResult::Failed;

		FRotator Rotator = (TargetActor->GetActorLocation() - Owner->GetActorLocation()).Rotation();
		Owner->SetActorRotation(Rotator);

		// �U���p�����^�[�W���Đ�
		AnimInstance->Montage_Play(AnimMontage, 2.0f);

		// �I���R�[���o�b�N���o�C���h
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UBTTask_EnemyAttack::OnMontageEnded, &OwnerComp);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, AnimMontage);

		// �܂��������Ă��Ȃ��̂� InProgress ��Ԃ�
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

// �����^�[�W���I������Succeeded��Ԃ����߂̃R�[���o�b�N
void UBTTask_EnemyAttack::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp)
	{
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}