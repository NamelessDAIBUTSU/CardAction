// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <UI/HUD/MapWidget.h>
#include "StageSelectController.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AStageSelectController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStageSelectController();

public:
	virtual void Tick(float DeltaSec) override;

protected:
	virtual void BeginPlay() override;

public:
	UMapWidget* GetMapWidget() { return MapWidget; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MapWidgetClass;

private:
	UPROPERTY()
	UMapWidget* MapWidget = nullptr;
};
