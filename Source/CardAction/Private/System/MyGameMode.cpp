// Fill out your copyright notice in the Description page of Project Settings.

#include "System/MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include <Camera/GridCamera.h>
#include <Character/MyCharacter.h>
#include <Grid/GridManager.h>
#include "Enemy/EnemyManager.h"
#include <Card/DeckManager.h>
#include <System/Phase/BattlePhaseBase.h>
#include <System/Phase/BattlePhase_Entry.h>
#include <System/Phase/BattlePhase_CardSelect.h>
#include <System/Phase/BattlePhase_Action.h>
#include <System/Phase/BattlePhase_Result.h>
#include <Character/MyPlayerController.h>
#include "Components/CapsuleComponent.h"

AMyGameMode::AMyGameMode()
{
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();

	// エネミーマネージャー生成
	if (EnemyManagerClass)
	{
		EnemyManager = GetWorld()->SpawnActor<AEnemyManager>(EnemyManagerClass, FVector(), FRotator());
	}

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

	// グリッド初期化
	GridManager->Initialize();

	// プレイヤーを生成
	ACharacter* PlayerPawn = GetWorld()->SpawnActor<ACharacter>(PlayerPawnClass, GridManager->GetPlayerSpawnPosition(), FRotator());
	if (PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn player pawn!"));
		return;
	}
	// 落下しないようにZ位置を補正
	UCapsuleComponent* Capsule = PlayerPawn->GetCapsuleComponent();
	if (Capsule)
	{
		FVector AdjustedPos = PlayerPawn->GetActorLocation();
		float HalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
		AdjustedPos.Z += HalfHeight;
		PlayerPawn->SetActorLocation(AdjustedPos);
	}

	// 生成したセル上にプレイヤーを登録
	GridManager->AddActorOnCell(PlayerPawn, GridManager->ConvertToGridCoord(PlayerPawn->GetActorLocation()));

	// プレイヤーのグリッド座標設定
	Player = Cast<AMyCharacter>(PlayerPawn);
	if (Player)
	{
		FVector2D SpawnCoord = GridManager->ConvertToGridCoord(GridManager->GetPlayerSpawnPosition());
		Player->SetCurrentCoord(SpawnCoord);
	}

	// プレイヤーコントローラーを取得してPossess
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (MyPC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Cast AMyPlayerController!"));
		return;
	}
	MyPC->Possess(PlayerPawn);

	// カメラ生成
	if (AGridCamera* Camera = GetWorld()->SpawnActor<AGridCamera>())
	{
		Camera->AdjustCameraToGrid();

		// プレイヤーのビューをこのカメラに固定
		MyPC->SetViewTargetWithBlend(Camera, 0.0f);
	}

	// デッキマネージャー生成
	if (DeckManagerClass)
	{
		DeckManager = GetWorld()->SpawnActor<ADeckManager>(DeckManagerClass, FVector(), FRotator());
		if (DeckManager)
		{
			// デッキの初期化
			DeckManager->Initialzie(InitDeckData);
		}
	}

	// 各種Widgetの初期化
	if (MyPC->MainHUDWidget)
	{
		MyPC->MainHUDWidget->InitializeWidgets();
	}

	// 最初のフェーズ設定
	ChangePhase(EBattlePhase::Entry);
}

void AMyGameMode::Tick(float DeltaSeconds)
{
	if (CurrentBattlePhase == nullptr)
		return;

	// 現在のフェーズの更新
	CurrentBattlePhase->OnTick(DeltaSeconds);

	// フェーズ切り替えのリクエストがあったらフェーズ切り替え
	if (CurrentBattlePhase->IsRequestChangePhase())
	{
		ChangePhase(CurrentBattlePhase->GetRequestNextPhase());
	}
}

void AMyGameMode::ChangePhase(EBattlePhase NextPhase)
{
	// フェーズ終了時処理
	if (CurrentBattlePhase)
	{
		CurrentBattlePhase->OnExit();
	}

	// 次のフェーズを生成
	switch (NextPhase)
	{
	case EBattlePhase::Entry:
		CurrentBattlePhase = NewObject<UBattlePhaseBase>(this, UBattlePhase_Entry::StaticClass());
		break;
	case EBattlePhase::CardSelect:
		CurrentBattlePhase = NewObject<UBattlePhaseBase>(this, UBattlePhase_CardSelect::StaticClass());
		break;
	case EBattlePhase::Action:
	{
		CurrentBattlePhase = NewObject<UBattlePhaseBase>(this, UBattlePhase_Action::StaticClass());

		// アクションフェーズ開始時の処理
		OnStartActionPhase.Broadcast();
		break;
	}
	case EBattlePhase::Result:
		CurrentBattlePhase = NewObject<UBattlePhaseBase>(this, UBattlePhase_Result::StaticClass());
		break;
	case EBattlePhase::End:
		CurrentBattlePhase = nullptr;
		break;
	default:
		break;
	}

	// フェーズ開始時処理
	if (CurrentBattlePhase)
	{
		CurrentBattlePhase->OnBegin();
	}
}

EBattlePhase AMyGameMode::GetCurrentButtlePhase() const
{
	if (CurrentBattlePhase == nullptr)
		return EBattlePhase();

	return CurrentBattlePhase->GetBattlePhase();
}

// アクションフェーズの場合、残り時間を取得
int AMyGameMode::GetRemainSec()
{
	UBattlePhase_Action* ActionPhase = Cast<UBattlePhase_Action>(CurrentBattlePhase);
	if (ActionPhase)
	{
		return ActionPhase->GetCurrentRemainSec();
	}

	return 0;
}

void AMyGameMode::OnGameOver()
{
	// ゲームオーバー処理を呼ぶ
	OnGameEnd.Broadcast();
}
