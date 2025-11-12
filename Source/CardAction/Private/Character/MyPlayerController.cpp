// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/MyPlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	if (MainHUDWidget)
	{
		MainHUDWidget->OnUpdate(DeltaSeconds);
	}
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);

			UE_LOG(LogTemp, Warning, TEXT("LocalPlayer: %s"), LocalPlayer ? *LocalPlayer->GetName() : TEXT("nullptr"));
		}
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// UI生成
	if (MainHUDWidgetClass)
	{
		MainHUDWidget = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDWidgetClass);
		if (MainHUDWidget)
		{
			// 描画命令
			MainHUDWidget->AddToViewport();
		}
	}

	// 少し遅らせてUI入力を有効にする
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyPlayerController::SetupUIInputMode, 0.1f, false);
}

void AMyPlayerController::SetupUIInputMode()
{
	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputMode);
}