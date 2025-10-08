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

	// �O���b�h����
	GridManager->GenerateGrid(GridManager->GenerateGridData);

	// �O���b�h��ɃG�l�~�[����
	GridManager->SpawnEnemies();

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
}

void AMyGameMode::Tick(float DeltaSeconds)
{
	switch (CurrentBattlePhase)
	{
		// �A�N�V�����^�C��
	case EBattlePhase::Action:
	{

		break;
	}
		// �J�[�h�I���^�C��
	case EBattlePhase::CardSelect:
	{

		break;
	}
	}
}

void AMyGameMode::OnGameOver()
{
	// �Q�[���I�[�o�[�������Ă�
	OnGameEnd.Broadcast();
}
