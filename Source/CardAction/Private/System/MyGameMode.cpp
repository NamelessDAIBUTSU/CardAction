// Fill out your copyright notice in the Description page of Project Settings.

#include "System/MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include <Camera/GridCamera.h>
#include <Character/MyCharacter.h>

AMyGameMode::AMyGameMode()
{
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();

	// グリッドマネージャー生成
	if (GridManagerClass)
	{
		GridManager = GetWorld()->SpawnActor<AGridManager>(GridManagerClass, FVector(), FRotator());
	}

	if (GridManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn GridManager!"));
		return;
	}

	// グリッド生成
	GridManager->GenerateGrid(GridManager->GenerateGridData);

	// グリッド上にエネミー生成
	GridManager->SpawnEnemies();

	// Pawn を Spawn
	APawn* PlayerPawn = GetWorld()->SpawnActor<APawn>(PlayerPawnClass, GridManager->GetPlayerSpawnPosition(), FRotator());
	if (PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn player pawn!"));
		return;
	}

	// 生成したセル上にプレイヤーを登録
	GridManager->AddActorOnCell(PlayerPawn, GridManager->ConvertToGridCoord(PlayerPawn->GetActorLocation()));

	// プレイヤーの座標設定
	Player = Cast<AMyCharacter>(PlayerPawn);
	if(Player)
	{
		FVector2D SpawnCoord = GridManager->ConvertToGridCoord(GridManager->GetPlayerSpawnPosition());
		Player->SetCurrentCoord(SpawnCoord);
	}

	// プレイヤーコントローラーを取得してPossess
	PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->Possess(PlayerPawn);
	}

	// カメラ生成
	if (AGridCamera* Camera = GetWorld()->SpawnActor<AGridCamera>())
	{
		Camera->AdjustCameraToGrid();

		// プレイヤーのビューをこのカメラに固定
		if (PlayerController)
		{
			PlayerController->SetViewTargetWithBlend(Camera, 0.0f);
		}
	}
}

void AMyGameMode::Tick(float DeltaSeconds)
{
	switch (CurrentBattlePhase)
	{
		// アクションタイム
	case EBattlePhase::Action:
	{

		break;
	}
		// カード選択タイム
	case EBattlePhase::CardSelect:
	{

		break;
	}
	}
}

void AMyGameMode::OnGameOver()
{
	// ゲームオーバー処理を呼ぶ
	OnGameEnd.Broadcast();
}
