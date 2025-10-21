// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridManager.h"
#include <Kismet/GameplayStatics.h>
#include <Character/MyCharacter.h>
#include "Grid/Cell/GridCellActor.h"
#include "Components/CapsuleComponent.h"

AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ������
void AGridManager::Initialize()
{
	// �O���b�h����
	GenerateGrid(GenerateGridData);

	// �O���b�h��ɃG�l�~�[����
	SpawnEnemies();
}

// �O���b�h����
void AGridManager::GenerateGrid(UGridData* GridData)
{
	if (GridData == nullptr)
		return;

	GenerateGridData = GridData;

	// �O���b�h�Z���̃X�|�[���ʒu
	FVector SpawnPosition = FVector::Zero();

	const auto& CellActors = GenerateGridData->GridCellActors;

	for (int32 Y = 0; Y < CellActors.Num(); ++Y)
	{
		TArray<AGridCellActor*> Row;

		for (int32 X = 0; X < CellActors[Y].RowCells.Num(); ++X)
		{
			// ��̃O���b�h�Z��
			if (CellActors[Y].RowCells[X] == nullptr)
			{
				Row.Add(nullptr);
			}
			// �ʏ�O���b�h�Z��
			else
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Name = *FString::Printf(TEXT("Grid_%d"), X + (Y * CellActors[Y].RowCells.Num()));
				SpawnParams.Owner = this;

				AGridCellActor* NewGridCell = GetWorld()->SpawnActor<AGridCellActor>(CellActors[Y].RowCells[X], SpawnPosition, FRotator(), SpawnParams);
				if (NewGridCell)
				{
					NewGridCell->CellData.GridCoord = ConvertToGridCoord(SpawnPosition);
					Row.Add(NewGridCell);
				}
			}

			// ���ɃX�|�[������ʒu��ݒ�
			if (X < CellActors[Y].RowCells.Num() - 1)
			{
				SpawnPosition.Y += GRID_CELL_UNIT;
			}
			// ���̍s�Ɉړ�
			else
			{
				SpawnPosition.X -= GRID_CELL_UNIT;
				SpawnPosition.Y = 0.f;
			}
		}

		// �s���e��o�^
		Grid.Add(Row);
	}
}

// �v���C���[���X�|�[�������郏�[���h���W�擾
FVector AGridManager::GetPlayerSpawnPosition()
{
	if(GenerateGridData == nullptr)
		return FVector();

	// �O���b�h�f�[�^�̃v���C���[�X�|�[���ʒu���烏�[���h���W���擾
	FVector PlayerSpawnPosition = ConvertToWorldPosition(GenerateGridData->PlayerSpawnCoord);

	// ���܂����Ⴄ�̂ŏ�����ɂ��炷
	PlayerSpawnPosition.Z = 300.f;

	return PlayerSpawnPosition;
}

// �A�N�Z�X�\�ȃO���b�h�Z����
bool AGridManager::IsAccessableGridCell(FVector CheckPosition)
{
	FVector2D Coord = ConvertToGridCoord(CheckPosition);
	AGridCellActor* GridCell = GetGridCellActor(Coord);
	if (GridCell == nullptr)
		return false;

	// �������肵�Ă���
	bool bIsAccessable = true;
	// �Z����ɃI�u�W�F�N�g������ĂȂ��Ȃ�OK
	bIsAccessable &= GridCell->IsExistActorOnCell() == false;
	// ��Z������Ȃ��Ȃ�OK
	bIsAccessable &= GridCell->CellData.GridCellType != EGridCellType::None;

	return bIsAccessable;
}


// �G�l�~�[���O���b�h��ɃX�|�[��
void AGridManager::SpawnEnemies()
{
	if (GenerateGridData == nullptr)
		return;

	// �X�|�[���\�ȍ��W�̎擾
	TArray<FVector2D> SpawnableCoords = GenerateGridData->EnemySpawnableCoords;

	for (auto Enemy : SpawnEnemyArray)
	{
		if (SpawnableCoords.IsEmpty())
			break;

		// �X�|�[������ʒu������
		int RandomIndex = FMath::RandRange(0, SpawnableCoords.Num() - 1);
		FVector2D SpawnCoord = SpawnableCoords[RandomIndex];
		FVector SpawnPosition = FVector(SpawnCoord.Y * GRID_CELL_UNIT * -1.f, SpawnCoord.X * GRID_CELL_UNIT, GRID_CELL_HEIGHT_UNIT * 0.5f);

		// �X�|�[��
		AEnemyBase* NewEnemy = GetWorld()->SpawnActor<AEnemyBase>(Enemy, SpawnPosition, FRotator(0.f, 180.f, 0.f));
		if (NewEnemy)
		{
			// �X�|�[���������Z���ɃA�N�^�[��ǉ�
			AddActorOnCell(NewEnemy, SpawnCoord);

			// Z�ʒu��␳
			UCapsuleComponent* Capsule = NewEnemy->GetCapsuleComponent();
			if (Capsule)
			{
				FVector AdjustedPos = NewEnemy->GetActorLocation();
				float HalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
				AdjustedPos.Z += HalfHeight * 1.1f;
				NewEnemy->SetActorLocation(AdjustedPos);
			}
		
			// ���W�̐ݒ�
			NewEnemy->SetCurrentCoord(SpawnCoord);
		}
		

		// �X�|�[���\�ʒu�����炷
		SpawnableCoords.RemoveAt(RandomIndex);
	}
}

// �Z����ɃA�N�^�[��o�^
void AGridManager::AddActorOnCell(AActor* Actor, FVector2D Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->AddActorOnCell(Actor);
	}
}

// �O���b�h�ォ��w��A�N�^�[�̏����폜
void AGridManager::RemoveActorFromGrid(AActor* Actor, FVector2D Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->RemoveActorFromCell(Actor);
	}
}

// �Z����̃A�N�^�[�Ƀ_���[�W����
void AGridManager::ExecuteAttackToGridCell(AActor* AttackedActor, float Damage, FVector2D Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->ExecuteAttackToActorOnCell(AttackedActor, Damage);
	}
}

// �Z����̃A�N�^�[���X�V
void AGridManager::RefleshActorInfoOnCell(AActor* MoveActor, FVector2D FromCoord, FVector2D ToCoord)
{
	if (MoveActor == nullptr)
		return;

	// �ړ����̃Z������A�N�^�[��������
	if (AGridCellActor* FromCell = GetGridCellActor(FromCoord))
	{
		FromCell->RemoveActorFromCell(MoveActor);
	}

	// �ړ���̃Z���ɃA�N�^�[����ǉ�
	if (AGridCellActor* ToCell = GetGridCellActor(ToCoord))
	{
		ToCell->AddActorOnCell(MoveActor);
	}
}

// �U���\����ǉ�
void AGridManager::AddAttackSign(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		TargetCell->AddAttackSign();
	}
}

// �U���\��������
void AGridManager::RemoveAttackSign(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		TargetCell->RemoveAttackSign();
	}
}

// �O���b�h��ɓG�����݂��邩
bool AGridManager::IsExistEnemyOnGrid()
{
	bool bIsExistEnemy = false;

	for (const auto& Col : Grid)
	{
		for (auto* Cell : Col)
		{
			if (Cell == nullptr)
				continue;

			// �G������
			if (Cell->IsExistEnemyOnCell())
			{
				return true;
			}
		}
	}

	return false;
}

// �O���b�h�}�X��ɓG�����݂��邩
bool AGridManager::IsExistEnemyOnGridCell(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->IsExistEnemyOnCell();
	}

	return false;
}

// �O���b�h�Z����ɂ���G�l�~�[���擾
AEnemyBase* AGridManager::GetEnemyOnGridCell(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->GetEnemyOnCell();
	}

	return nullptr;
}

// �O���b�h���W �� ���[���h���W�ɕϊ�
FVector AGridManager::ConvertToWorldPosition(FVector2D Coord)
{
	// �������X���̂��߁ACoord.X��Coord.Y���t�Ɏg�p
	FVector Position = FVector(Coord.Y * GRID_CELL_UNIT * -1.f, Coord.X * GRID_CELL_UNIT, GRID_CELL_HEIGHT_UNIT * 0.5f);

	return Position;
}

// ���[���h���W �� �O���b�h���W�ɕϊ�
FVector2D AGridManager::ConvertToGridCoord(FVector Position)
{
	// �������X���̂��߁ACoord.X��Coord.Y���t�Ɏg�p
	FVector2D Coord = FVector2D(Position.Y / GRID_CELL_UNIT, (Position.X * -1.f) / GRID_CELL_UNIT);

	return Coord;
}

// ��̍��W�� �c�E���E�΂� �̂����ꂩ�̐���ɂ��邩
bool AGridManager::IsSameLine(FVector2D Coord1, FVector2D Coord2)
{
	bool bIsSameLine = false;

	// ��
	bIsSameLine |= Coord1.X == Coord2.X;
	// �c
	bIsSameLine |= Coord1.Y == Coord2.Y;
	// �΂�
	bIsSameLine |= FMath::Abs(Coord1.X + Coord1.Y) == FMath::Abs(Coord2.X + Coord2.Y);

	return bIsSameLine;
}

// �v���C���[�Ǝw����W��������ɂ��邩
bool AGridManager::IsPlayerSameLine(FVector2D Coord)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
		return false;
	APawn* Pawn = PlayerController->GetPawn();
	if (Pawn == nullptr)
		return false;

	// �v���C���[�L�����N�^�[���ɃA�N�Z�X
	AMyCharacter* Player = Cast<AMyCharacter>(Pawn);
	if (Player)
	{
		return IsSameLine(Coord, Player->GetCurrentCoord());
	}

	return false;
}

// �O���b�h���W�͈͊O�`�F�b�N
bool AGridManager::IsInGrid(FVector2D Coord)
{
	if (Coord.Y < 0 || Grid.Num() <= Coord.Y)
		return false;
	if (Coord.X < 0 || Grid[Coord.Y].Num() <= Coord.X)
		return false;

	return true;
}

// �O���b�h�Z�����擾
AGridCellActor* AGridManager::GetGridCellActor(FVector2D Coord)
{
	if (IsInGrid(Coord) == false)
		return nullptr;

	return Grid[Coord.Y][Coord.X];
}
AGridCellActor* AGridManager::GetGridCellActor(FVector Position)
{
	FVector2D Coord = ConvertToGridCoord(Position);
	return GetGridCellActor(Coord);
}

// �O���b�h�T�C�Y�̎擾
FVector2D AGridManager::GetGridSize()
{
	if (Grid.IsEmpty())
		return FVector2D::Zero();

	return FVector2D(Grid[0].Num(), Grid.Num());
}