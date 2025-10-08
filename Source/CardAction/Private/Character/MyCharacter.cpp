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
}

// 入力バインド設定
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComp))
	{
		// 攻撃
		EnhancedInputComp->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::OnAttack);
		// 回避
		EnhancedInputComp->BindAction(EscapeAction, ETriggerEvent::Started, this, &AMyCharacter::OnEscape);

		if (GridMovementComp)
		{
			// グリッド移動
			EnhancedInputComp->BindAction(MoveGridAction, ETriggerEvent::Triggered, GridMovementComp, &UGridMovementComponent::OnMoveToDirection);
			EnhancedInputComp->BindAction(MoveGridAction, ETriggerEvent::Completed, GridMovementComp, &UGridMovementComponent::OnResetDirectionCache);
			// 向く
			EnhancedInputComp->BindAction(TurnTowardAction, ETriggerEvent::Started, GridMovementComp, &UGridMovementComponent::OnChangeTurnMode);
			EnhancedInputComp->BindAction(TurnTowardAction, ETriggerEvent::Completed, GridMovementComp, &UGridMovementComponent::OnChangeTurnMode);
			
			EnhancedInputComp->BindAction(ExecuteCards, ETriggerEvent::Started, this, &AMyCharacter::OnExecuteCards);
		}
	}
}

// AWSD移動
void AMyCharacter::OnMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// コントローラのYaw回転を取得
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// 前方向/右方向を取得
		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 移動入力をAddMovementInputで適用
		AddMovementInput(ForwardDir, MovementVector.Y);
		AddMovementInput(RightDir, MovementVector.X);
	}
}

// 攻撃
void AMyCharacter::OnAttack(const FInputActionValue& Value)
{
	if (EquippedWeapon == nullptr)
		return;

	// 装備武器の攻撃処理を呼び出す
	EquippedWeapon->OnAttack();
}

// 回避
void AMyCharacter::OnEscape(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(Controller);
		if (PlayerController && PlayerController->MainHUDWidget)
		{
			auto* HandCardsWidget = PlayerController->MainHUDWidget->HandCardsWidget;
			if (HandCardsWidget)
			{
				HandCardsWidget->AddToHandCards(DefaultCardData);
			}
		}
	}
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

// 選択中カード発動
void AMyCharacter::OnExecuteCards(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(Controller);
		if (PlayerController && PlayerController->MainHUDWidget)
		{
			auto* SelectedCardsWidget = PlayerController->MainHUDWidget->SelectedCardsWidget;
			if (SelectedCardsWidget)
			{
				SelectedCardsWidget->OnExecute();
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

// 武器を装備する
void AMyCharacter::EquipWeapon(AWeaponActorBase* Weapon)
{
	if (Weapon == nullptr)
		return;

	EquippedWeapon = Weapon;

	// 所有者の設定
	EquippedWeapon->SetOwner(this);

	// 武器の見た目をプレイヤーの手に追従させる
	EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_r"));
}
