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
#include "Card/DeckManager.h"

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

	// ��D�J�[�h�̔z��̃T�C�Y�m��
	HandCards.Reserve(MAX_HAND_CARDS_NUM);
}

// ���̓o�C���h�ݒ�
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComp))
	{
		// �J�[�h����
		EnhancedInputComp->BindAction(UseCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnUseCard);
		// �J�[�h�I��
		EnhancedInputComp->BindAction(SelectFirstCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectFirstCard);
		EnhancedInputComp->BindAction(SelectSecondCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectSecondCard);
		EnhancedInputComp->BindAction(SelectThirdCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectThirdCard);
		EnhancedInputComp->BindAction(SelectFourthCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectFourthCard);
		EnhancedInputComp->BindAction(ScrollSelectCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnScrollSelectCard);

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

// �J�[�h����
void AMyCharacter::OnUseCard(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController);
	if (MyPlayerController == nullptr)
		return;

	if (MyPlayerController->MainHUDWidget && MyPlayerController->MainHUDWidget->HandCardsWidget)
	{
		MyPlayerController->MainHUDWidget->HandCardsWidget->ExecuteEffect(SelectHandCardsIndex);
	}
}

// �J�[�h�I��
void AMyCharacter::OnSelectFirstCard(const FInputActionValue& Value)
{
	SelectHandCardsIndex = 0;

	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
	{
		if (MyGM->DeckManager)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController);
			if (MyPlayerController == nullptr)
				return;

			if (MyPlayerController->MainHUDWidget && MyPlayerController->MainHUDWidget->HandCardsWidget)
			{
				MyPlayerController->MainHUDWidget->HandCardsWidget->AddToHandCards(SelectHandCardsIndex, MyGM->DeckManager->DrawCardFromTop());
			}
		}
	}

	// �E�B�W�F�b�g�ɔ��f
	RefleshHandCards();
}

void AMyCharacter::OnSelectSecondCard(const FInputActionValue& Value)
{
	SelectHandCardsIndex = 1;

	// �E�B�W�F�b�g�ɔ��f
	RefleshHandCards();
}

void AMyCharacter::OnSelectThirdCard(const FInputActionValue& Value)
{
	SelectHandCardsIndex = 2;

	// �E�B�W�F�b�g�ɔ��f
	RefleshHandCards();
}

void AMyCharacter::OnSelectFourthCard(const FInputActionValue& Value)
{
	SelectHandCardsIndex = 3;

	// �E�B�W�F�b�g�ɔ��f
	RefleshHandCards();
}

void AMyCharacter::OnScrollSelectCard(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	if (AxisValue > 0.f)
	{
		SelectHandCardsIndex = FMath::Min(MAX_HAND_CARDS_NUM - 1, SelectHandCardsIndex + 1);
	}
	else if (AxisValue < 0.f)
	{
		SelectHandCardsIndex = FMath::Max(0, SelectHandCardsIndex - 1);
	}

	// �E�B�W�F�b�g�ɔ��f
	RefleshHandCards();
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

// ��D�ɃJ�[�h��ǉ�
void AMyCharacter::AddToHandCards(UCardData* CardData)
{
	// �����ς��Ȃ̂Œǉ��ł��܂��[��
	if (HandCards.Num() == MAX_HAND_CARDS_NUM)
		return;

	HandCards.Add(CardData);
}

// ��D����J�[�h������
void AMyCharacter::RemoveFromHandCards(UCardData* CardData)
{
	HandCards.Remove(CardData);

	// ���Ԃ��l�߂�

}

// ��D�E�B�W�F�b�g�ɔ��f
void AMyCharacter::RefleshHandCards()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController);
	if (MyPlayerController == nullptr)
		return;

	if (MyPlayerController->MainHUDWidget && MyPlayerController->MainHUDWidget->HandCardsWidget)
	{
		MyPlayerController->MainHUDWidget->HandCardsWidget->SelectCard(SelectHandCardsIndex);
	}
}
