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

AMyGameMode::AMyGameMode()
{
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();

	// �G�l�~�[�}�l�[�W���[����
	if (EnemyManagerClass)
	{
		EnemyManager = GetWorld()->SpawnActor<AEnemyManager>(EnemyManagerClass, FVector(), FRotator());
	}

	// �O���b�h�}�l�[�W���[����
	if (GridManagerClass)
	{
		GridManager = GetWorld()->SpawnActor<AGridManager>(GridManagerClass, FVector(), FRotator());
	}

	if (GridManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn GridManager!"));
		return;
	}

	// �O���b�h������
	GridManager->Initialize();

	// Pawn �� Spawn
	APawn* PlayerPawn = GetWorld()->SpawnActor<APawn>(PlayerPawnClass, GridManager->GetPlayerSpawnPosition(), FRotator());
	if (PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn player pawn!"));
		return;
	}

	// ���������Z����Ƀv���C���[��o�^
	GridManager->AddActorOnCell(PlayerPawn, GridManager->ConvertToGridCoord(PlayerPawn->GetActorLocation()));

	// �v���C���[�̍��W�ݒ�
	Player = Cast<AMyCharacter>(PlayerPawn);
	if(Player)
	{
		FVector2D SpawnCoord = GridManager->ConvertToGridCoord(GridManager->GetPlayerSpawnPosition());
		Player->SetCurrentCoord(SpawnCoord);
	}

	// �v���C���[�R���g���[���[���擾����Possess
	PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->Possess(PlayerPawn);
	}

	// �J��������
	if (AGridCamera* Camera = GetWorld()->SpawnActor<AGridCamera>())
	{
		Camera->AdjustCameraToGrid();

		// �v���C���[�̃r���[�����̃J�����ɌŒ�
		if (PlayerController)
		{
			PlayerController->SetViewTargetWithBlend(Camera, 0.0f);
		}
	}

	// �f�b�L�}�l�[�W���[����
	if (DeckManagerClass)
	{
		DeckManager = GetWorld()->SpawnActor<ADeckManager>(DeckManagerClass, FVector(), FRotator());
		if (DeckManager)
		{
			// �f�b�L�̏�����
			DeckManager->Initialzie(InitDeckData);
		}
	}

	// �ŏ��̃t�F�[�Y�ݒ�
	ChangePhase(EBattlePhase::Entry);
}

void AMyGameMode::Tick(float DeltaSeconds)
{
	if (CurrentBattlePhase == nullptr)
		return;

	// ���݂̃t�F�[�Y�̍X�V
	CurrentBattlePhase->OnTick(DeltaSeconds);

	// �t�F�[�Y�؂�ւ��̃��N�G�X�g����������t�F�[�Y�؂�ւ�
	if (CurrentBattlePhase->IsRequestChangePhase())
	{
		ChangePhase(CurrentBattlePhase->GetRequestNextPhase());
	}
}

void AMyGameMode::ChangePhase(EBattlePhase NextPhase)
{
	// �t�F�[�Y�I��������
	if (CurrentBattlePhase)
	{
		CurrentBattlePhase->OnExit();
	}

	// ���̃t�F�[�Y�𐶐�
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

		// �A�N�V�����t�F�[�Y�J�n���̏���
		OnStartActionPhase.Broadcast();

		break;
	}
	case EBattlePhase::Result:
		CurrentBattlePhase = NewObject<UBattlePhaseBase>(this, UBattlePhase_Result::StaticClass());
		break;
	default:
		break;
	}

	// �t�F�[�Y�J�n������
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

void AMyGameMode::OnGameOver()
{
	// �Q�[���I�[�o�[�������Ă�
	OnGameEnd.Broadcast();
}
