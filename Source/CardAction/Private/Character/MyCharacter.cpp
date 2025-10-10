// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Character/MyPlayerController.h"

AMyCharacter::AMyCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// �R���g���[���[�̉�]�𐧌�
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 2D���ʂɐ���
	if (UCharacterMovementComponent* CharacterMovementComp = GetCharacterMovement())
	{
		CharacterMovementComp->bConstrainToPlane = true;
		CharacterMovementComp->bSnapToPlaneAtStart = true;
	}

	// �O���b�h�ړ��R���|�[�l���g
	GridMovementComp = CreateDefaultSubobject<UGridMovementComponent>(TEXT("GridMovement"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// ���̓o�C���h�ݒ�
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComp))
	{
		// ���픭��
		EnhancedInputComp->BindAction(UseWeaponAction, ETriggerEvent::Started, this, &AMyCharacter::OnUseWeapon);
		// �A�V�X�g����
		EnhancedInputComp->BindAction(UseAssistAction, ETriggerEvent::Started, this, &AMyCharacter::OnUseAssist);

		if (GridMovementComp)
		{
			// �O���b�h�ړ�
			EnhancedInputComp->BindAction(MoveGridAction, ETriggerEvent::Triggered, GridMovementComp, &UGridMovementComponent::OnMoveToDirection);
			EnhancedInputComp->BindAction(MoveGridAction, ETriggerEvent::Completed, GridMovementComp, &UGridMovementComponent::OnResetDirectionCache);
			// ����
			EnhancedInputComp->BindAction(TurnTowardAction, ETriggerEvent::Started, GridMovementComp, &UGridMovementComponent::OnChangeTurnMode);
			EnhancedInputComp->BindAction(TurnTowardAction, ETriggerEvent::Completed, GridMovementComp, &UGridMovementComponent::OnChangeTurnMode);
		}
	}
}

// ���픭��
void AMyCharacter::OnUseWeapon(const FInputActionValue& Value)
{
	if (EquippedWeapon == nullptr)
		return;

	// ��������̍U���������Ăяo��
	EquippedWeapon->OnAttack();
}

// �A�V�X�g����
void AMyCharacter::OnUseAssist(const FInputActionValue& Value)
{
	
}

// �_���[�W����
void AMyCharacter::OnTakeDamage(float Damage)
{
	// �_���[�W���󂯂�
	CurrentHP = FMath::Max(CurrentHP - Damage, 0.f);

	// GameMode�̃Q�[���I�[�o�[�������Ă�
	if (CurrentHP == 0)
	{
		if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
		{
			if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
			{
				MyGameMode->OnGameOver();
			}
		}
	}
}

void AMyCharacter::SetCurrentCoord(FVector2D Coord)
{
	if (GridMovementComp)
	{
		GridMovementComp->SetCoord(Coord);
	}
}

FVector2D AMyCharacter::GetCurrentCoord() const
{
	if (GridMovementComp)
	{
		return GridMovementComp->GetCurrentCoord();
	}

	return FVector2D::Zero();
}

// ����𑕔�����
void AMyCharacter::EquipWeapon(AWeaponActorBase* Weapon)
{
	if (Weapon == nullptr)
		return;

	EquippedWeapon = Weapon;

	// ���L�҂̐ݒ�
	EquippedWeapon->SetOwner(this);

	// ����̌����ڂ��v���C���[�̎�ɒǏ]������
	EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_r"));
}
