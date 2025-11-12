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
#include <UI/HUD/HPBar.h>

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

	// HPバー用ウィジェットコンポーネント
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	if (WidgetComp)
	{
		WidgetComp->SetupAttachment(RootComponent);
		// シャドウを落とさない
		WidgetComp->SetCastShadow(false);
		// デカールも受けない
		WidgetComp->bReceivesDecals = false;
		// 当たり判定も不要
		WidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// ポーン同士は当たらないようにする
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyCharacter::Tick(float DeltaSeconds)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では時間停止
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Entry && MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
	{
		this->CustomTimeDilation = 0.f;
		return;
	}

	this->CustomTimeDilation = 1.f;

    Super::Tick(DeltaSeconds);
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 手札カードの配列のサイズ確保
	HandCards.Reserve(MAX_HAND_CARDS_NUM);

	// ウィジェットに反映
	RefleshHandCards();

	// HPバーに所有者を登録
	if (WidgetComp)
	{
		if (UHPBar* HPWidget = Cast<UHPBar>(WidgetComp->GetUserWidgetObject()))
		{
			// HP取得用の関数設定
			FOnGetMaxHP GetMaxHPFunc;
			GetMaxHPFunc.BindLambda([this]()
				{
					if (IsValid(this) == false)
						return 0;

					return MaxHP;
				});

			FOnGetCurrentHP GetCurrentHPFunc;
			GetCurrentHPFunc.BindLambda([this]()
				{
					if (IsValid(this) == false)
						return 0;

					return CurrentHP;
				});
			HPWidget->Setup(WidgetComp, GetMaxHPFunc, GetCurrentHPFunc);

			// エネミー用のレイアウトに変更
			HPWidget->ChangeLayout(EHPBarType::Player);
		}
	}
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
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では処理をしない
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
		return;

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
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では処理をしない
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
		return;

	SelectHandCardsIndex = 0;

	// ウィジェットに反映
	RefleshHandCards();
}

void AMyCharacter::OnSelectSecondCard(const FInputActionValue& Value)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では処理をしない
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
		return;

	SelectHandCardsIndex = 1;

	// ウィジェットに反映
	RefleshHandCards();
}

void AMyCharacter::OnSelectThirdCard(const FInputActionValue& Value)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では処理をしない
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
		return;

	SelectHandCardsIndex = 2;

	// ウィジェットに反映
	RefleshHandCards();
}

void AMyCharacter::OnSelectFourthCard(const FInputActionValue& Value)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では処理をしない
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
		return;

	SelectHandCardsIndex = 3;

	// ウィジェットに反映
	RefleshHandCards();
}

void AMyCharacter::OnScrollSelectCard(const FInputActionValue& Value)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では処理をしない
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
		return;

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
	// 無敵中なら無視
	if (bIsInvincible)
		return;

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

	// 無敵時間の開始
	StartInvincible();
}

void AMyCharacter::SetCurrentCoord(FCoord Coord)
{
	if (GridMovementComp)
	{
		GridMovementComp->SetCoord(Coord);
	}
}

FCoord AMyCharacter::GetCurrentCoord() const
{
	if (GridMovementComp)
	{
		return GridMovementComp->GetCurrentCoord();
	}

	return FCoord::Zero();
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

// ダメージによる点滅
void AMyCharacter::StartBlinkEffect()
{
	GetWorldTimerManager().SetTimer(BlinkTimer, this, &AMyCharacter::ToggleBlink, 0.1f, true);
}

void AMyCharacter::ToggleBlink()
{
	if (auto* MeshComp = GetMesh())
	{
		MeshComp->SetVisibility(!MeshComp->GetVisibleFlag());
	}
}

void AMyCharacter::EndInvincible()
{
	if (auto* MeshComp = GetMesh())
	{
		bIsInvincible = false;
		GetWorldTimerManager().ClearTimer(BlinkTimer);

		MeshComp->SetVisibility(true);
	}
}

// 無敵時間の開始
void AMyCharacter::StartInvincible()
{
	bIsInvincible = true;

	// 点滅演出開始
	StartBlinkEffect();

	// 終了時のコールバック設定
	GetWorldTimerManager().SetTimer(InvincibleTimer, this, &AMyCharacter::EndInvincible, 2.0f, false);
}

//// 無敵時間の更新
//void AMyCharacter::UpdateInvincible(float DeltaSec)
//{
//	if (bIsInvincible == false)
//		return;
//
//	ElapsedSec += DeltaSec;
//
//	// 無敵時間終了
//	if (ElapsedSec >= InvincibleSec)
//	{
//		bIsInvincible = false;
//
//		// 点滅演出終了
//		StopBlinkEffect();
//	}
//}
