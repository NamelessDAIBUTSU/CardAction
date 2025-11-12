// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <UI/HUD/MapWidget.h>
#include "StageSelectGameMode.generated.h"

UCLASS()
class CARDACTION_API AStageSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStageSelectGameMode();

public:
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSec) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMapData* GenerateMapData = nullptr;

private:
	UPROPERTY()
	class UMapManager* MapManager = nullptr;
};
