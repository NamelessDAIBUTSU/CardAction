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

	// コントローラーの回転を制限
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 2D平面に制約
	if (UCharacterMovementComponent* CharacterMovementComp = GetCharacterMovement())
	{
		CharacterMovementComp->bConstrainToPlane = true;
		CharacterMovementComp->bSnapToPlaneAtStart = true;
	}

	// グリッド移動コンポーネント
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

	// 手札カードの配列のサイズ確保
	HandCards.Reserve(MAX_HAND_CARDS_NUM);
}

// 入力バインド設定
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComp))
	{
		// カード発動
		EnhancedInputComp->BindAction(UseCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnUseCard);
		// カード選択
		EnhancedInputComp->BindAction(SelectFirstCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectFirstCard);
		EnhancedInputComp->BindAction(SelectSecondCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectSecondCard);
		EnhancedInputComp->BindAction(SelectThirdCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectThirdCard);
		EnhancedInputComp->BindAction(SelectFourthCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnSelectFourthCard);
		EnhancedInputComp->BindAction(ScrollSelectCardAction, ETriggerEvent::Started, this, &AMyCharacter::OnScrollSelectCard);

		if (GridMovementComp)
		{
			// グリッド移動
			EnhancedInputComp->BindAction(MoveGridAction, ETriggerEvent::Triggered, GridMovementComp, &UGridMovementComponent::OnMoveToDirection);
			EnhancedInputComp->BindAction(MoveGridAction, ETriggerEvent::Completed, GridMovementComp, &UGridMovementComponent::OnResetDirectionCache);
			// 向く
			EnhancedInputComp->BindAction(TurnTowardAction, ETriggerEvent::Started, GridMovementComp, &UGridMovementComponent::OnChangeTurnMode);
			EnhancedInputComp->BindAction(TurnTowardAction, ETriggerEvent::Completed, GridMovementComp, &UGridMovementComponent::OnChangeTurnMode);
		}
	}
}

// カード発動
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

// カード選択
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

	// ウィジェットに反映
	RefleshHandCards();
}

void AMyCharacter::OnSelectSecondCard(const FInputActionValue& Value)
{
	SelectHandCardsIndex = 1;

	// ウィジェットに反映
	RefleshHandCards();
}

void AMyCharacter::OnSelectThirdCard(const FInputActionValue& Value)
{
	SelectHandCardsIndex = 2;

	// ウィジェットに反映
	RefleshHandCards();
}

void AMyCharacter::OnSelectFourthCard(const FInputActionValue& Value)
{
	SelectHandCardsIndex = 3;

	// ウィジェットに反映
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

	// ウィジェットに反映
	RefleshHandCards();
}

// ダメージ処理
void AMyCharacter::OnTakeDamage(float Damage)
{
	// ダメージを受ける
	CurrentHP = FMath::Max(CurrentHP - Damage, 0.f);

	// GameModeのゲームオーバー処理を呼ぶ
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

// 手札にカードを追加
void AMyCharacter::AddToHandCards(UCardData* CardData)
{
	// いっぱいなので追加できませーん
	if (HandCards.Num() == MAX_HAND_CARDS_NUM)
		return;

	HandCards.Add(CardData);
}

// 手札からカードを除去
void AMyCharacter::RemoveFromHandCards(UCardData* CardData)
{
	HandCards.Remove(CardData);

	// 順番を詰める

}

// 手札ウィジェットに反映
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
