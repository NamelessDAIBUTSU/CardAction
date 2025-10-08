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
		MainHUDWidget->OnTick(DeltaSeconds);
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

	// UIê∂ê¨
	if (MainHUDWidgetClass)
	{
		MainHUDWidget = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDWidgetClass);
		if (MainHUDWidget)
		{
			// ï`âÊñΩóﬂ
			MainHUDWidget->AddToViewport();
		}
	}
}