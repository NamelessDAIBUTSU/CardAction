// Fill out your copyright notice in the Description page of Project Settings.


#include "MyComponents/GridMovementComponent.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

// Sets default values for this component's properties
UGridMovementComponent::UGridMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGridMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGridMovementComponent::MoveToDirection(FVector Direction)
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr)
		return;

	APawn* PawnOwner = Cast<APawn>(Owner);
	if (PawnOwner == nullptr)
		return;

	AController* Controller = PawnOwner->GetController();
	if (Controller == nullptr)
		return;

	// �ړ����͈ړ��I������̂�
	if (IsFinishGridMove() == false)
		return;

	// �R���g���[����Yaw��]���擾
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// �O����/�E�������擾
	const FVector UpDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// ���[���h���ɍ��킹�Đi�s�����p�̃x�N�g�����쐬
	// #MEMO : �������X���A�E������Y���̂��߁ADirection(1.f, 0.f)�Ȃ�RightDirection���g�p
	FVector MoveDirection;
	if (Direction.X != 0.f)
	{
		MoveDirection = RightDirection * Direction.X;
	}
	else if (Direction.Y != 0.f)
	{
		MoveDirection = UpDirection * Direction.Y;
	}

	// �����n�_���v�Z
	TargetLocation = Owner->GetActorLocation() + MoveDirection * GridUnit;

	// �O��̐i�s�����Ɠ����ł���Δ�����
	if (DirectionCache.Equals(MoveDirection))
		return;

	// �i�s�����ɉ�]
	FRotator NextRotation = (TargetLocation - Owner->GetActorLocation()).Rotation();
	Owner->SetActorRotation(NextRotation);

	// �����ύX�t���O�������Ă��Ȃ��Ȃ�A�O���b�h�ړ�
	if (bIsTurningMode == false)
	{
		if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
		{
			if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
			{
				auto* GridManager = MyGameMode->GridManager;
				if (GridManager == nullptr)
					return;

				// �i�s�����̃O���b�h���i�s�\��Ԃ�
				if (GridManager->IsAccessableGridCell(TargetLocation) == false)
				{
					return;
				}

				// �ړ����t���O�𗧂Ă�
				bIsMoving = true;

				// �O���b�h�}�l�[�W���[�̃A�N�^�[�̈ʒu�����X�V
				FVector2D FromCell = GridManager->ConvertToGridCoord(Owner->GetActorLocation());
				FVector2D ToCell = GridManager->ConvertToGridCoord(TargetLocation);
				GridManager->RefleshActorInfoOnCell(Owner, FromCell, ToCell);

				// �ʒu�ݒ�
				Owner->SetActorLocation(TargetLocation);

				// ���W�ݒ�
				SetCoord(ToCell);
			}
		}
	}

	// �L���b�V���̍X�V
	DirectionCache = MoveDirection;
}

void UGridMovementComponent::OnMoveToDirection(const FInputActionValue& Value)
{
	// �ړ����͈ړ��I������̂�
	if (IsFinishGridMove() == false)
		return;

	// �ړ��ʂ̎擾
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// �i�s�����̎擾
	FVector2D Dir;
	if (FMath::Abs(MovementVector.X) < FMath::Abs(MovementVector.Y))
	{
		Dir = FVector2D(0.f, MovementVector.Y);
	}
	if (FMath::Abs(MovementVector.X) >= FMath::Abs(MovementVector.Y))
	{
		Dir = FVector2D(MovementVector.X, 0.f);
	}
	// ���K��
	Dir = Dir.GetSafeNormal();

	MoveToDirection(FVector(Dir.X, Dir.Y, 0.f));
}

// �ړ������L���b�V���̍폜
void UGridMovementComponent::OnResetDirectionCache(const FInputActionValue& Value)
{
	DirectionCache = FVector::Zero();
}

void UGridMovementComponent::OnChangeTurnMode(const FInputActionValue& Value)
{
	// ���������ύX����t���O���X�V
	bIsTurningMode = Value.Get<bool>();
}

// �O���b�h�ړ����I��������
bool UGridMovementComponent::IsFinishGridMove()
{
	// �ړ�������Ȃ�
	if (bIsMoving == false)
		return true;

	AActor* Owner = GetOwner();
	if (Owner == nullptr)
		return true;

	// �ړ��I��
	if (TargetLocation.Equals(Owner->GetActorLocation()))
	{
		bIsMoving = false;
		return true;
	}
	// �ړ���
	else
	{
		return false;
	}
}


