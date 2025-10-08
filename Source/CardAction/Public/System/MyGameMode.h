// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include <Grid/GridManager.h>
#include <System/Phase/BattlePhaseDef.h>
#include "MyGameMode.generated.h"

UCLASS()
class CARDACTION_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

public:
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
	void OnGameOver();

public:
	// 生成するプレイヤー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<APawn> PlayerPawnClass;

	// グリッドマネージャー
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TSubclassOf<AGridManager> GridManagerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	AGridManager* GridManager;

	// ゲーム終了時に発火するデリゲート
	DECLARE_MULTICAST_DELEGATE(FOnGameEnd);
	FOnGameEnd OnGameEnd;

private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	EBattlePhase CurrentBattlePhase = EBattlePhase::CardSelect;

	// プレイヤー
	UPROPERTY(VisibleAnywhere, Category = "Player")
	class AMyCharacter* Player = nullptr;

	// プレイヤーコントローラー
	UPROPERTY(VisibleAnywhere, Category = "Player")
	APlayerController* PlayerController = nullptr;
};
