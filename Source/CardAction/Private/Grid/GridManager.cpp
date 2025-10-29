// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridManager.h"
#include <Kismet/GameplayStatics.h>
#include <Character/MyCharacter.h>
#include "Grid/Cell/GridCellActor.h"
#include "Components/CapsuleComponent.h"
#include <Map/MapManager.h>

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

// 初期化
void AGridManager::Initialize()
{
	// グリッド生成
	GenerateGrid();

	// グリッド上にエネミー生成
	SpawnEnemies();
}

// グリッド生成
void AGridManager::GenerateGrid()
{
	// 生成するグリッドデータの取得
	UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr || MapManager->GetCurrentStage() == nullptr)
		return;

	GenerateGridData = MapManager->GetCurrentStage()->GetGridData();
	if (GenerateGridData == nullptr)
		return;

	// グリッドセルのスポーン位置
	FVector SpawnPosition = FVector::Zero();

	const auto& CellActors = GenerateGridData->GridCellActors;

	for (int32 Y = 0; Y < CellActors.Num(); ++Y)
	{
		TArray<AGridCellActor*> Row;

		for (int32 X = 0; X < CellActors[Y].RowCells.Num(); ++X)
		{
			// 空のグリッドセル
			if (CellActors[Y].RowCells[X] == nullptr)
			{
				Row.Add(nullptr);
			}
			// 通常グリッドセル
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

			// 次にスポーンする位置を設定
			if (X < CellActors[Y].RowCells.Num() - 1)
			{
				SpawnPosition.Y += GRID_CELL_UNIT;
			}
			// 次の行に移動
			else
			{
				SpawnPosition.X -= GRID_CELL_UNIT;
				SpawnPosition.Y = 0.f;
			}
		}

		// 行内容を登録
		Grid.Add(Row);
	}
}

// プレイヤーをスポーンさせるワールド座標取得
FVector AGridManager::GetPlayerSpawnPosition()
{
	if(GenerateGridData == nullptr)
		return FVector();

	// グリッドデータのプレイヤースポーン位置からワールド座標を取得
	FVector PlayerSpawnPosition = ConvertToWorldPosition(GenerateGridData->PlayerSpawnCoord);

	return PlayerSpawnPosition;
}

// アクセス可能なグリッドセルか
bool AGridManager::IsAccessableGridCell(FVector CheckPosition)
{
	FVector2D Coord = ConvertToGridCoord(CheckPosition);
	return IsAccessableGridCell(Coord);
}
bool AGridManager::IsAccessableGridCell(FVector2D Coord)
{
	AGridCellActor* GridCell = GetGridCellActor(Coord);
	if (GridCell == nullptr)
		return false;

	bool bIsAccessable = true;
	// 以下、条件判定
	// セル上にオブジェクトが乗ってないならOK
	bIsAccessable &= GridCell->IsExistActorOnCell() == false;
	// 空セルじゃないならOK
	bIsAccessable &= GridCell->CellData.GridCellType != EGridCellType::None;

	return bIsAccessable;
}

// エネミーをグリッド上にスポーン
void AGridManager::SpawnEnemies()
{
	if (GenerateGridData == nullptr)
		return;

	// スポーン可能な座標の取得
	TArray<FVector2D> SpawnableCoords = GenerateGridData->EnemySpawnableCoords;

	for (auto Enemy : SpawnEnemyArray)
	{
		if (SpawnableCoords.IsEmpty())
			break;

		// スポーンする位置を決定
		int RandomIndex = FMath::RandRange(0, SpawnableCoords.Num() - 1);
		FVector2D SpawnCoord = SpawnableCoords[RandomIndex];
		FVector SpawnPosition = FVector(SpawnCoord.Y * GRID_CELL_UNIT * -1.f, SpawnCoord.X * GRID_CELL_UNIT, GRID_CELL_HEIGHT_UNIT * 0.5f);

		// スポーン
		AEnemyBase* NewEnemy = GetWorld()->SpawnActor<AEnemyBase>(Enemy, SpawnPosition, FRotator(0.f, 180.f, 0.f));
		if (NewEnemy)
		{
			// スポーンさせたセルにアクターを追加
			AddActorOnCell(NewEnemy, SpawnCoord);

			// Z位置を補正
			UCapsuleComponent* Capsule = NewEnemy->GetCapsuleComponent();
			if (Capsule)
			{
				FVector AdjustedPos = NewEnemy->GetActorLocation();
				float HalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
				AdjustedPos.Z += HalfHeight * 1.1f;
				NewEnemy->SetActorLocation(AdjustedPos);
			}
		
			// 座標の設定
			NewEnemy->SetCurrentCoord(SpawnCoord);
		}
		

		// スポーン可能位置を減らす
		SpawnableCoords.RemoveAt(RandomIndex);
	}
}

// セル上にアクターを登録
void AGridManager::AddActorOnCell(AActor* Actor, FVector2D Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->AddActorOnCell(Actor);
	}
}

// セル上から指定アクターの情報を削除
void AGridManager::RemoveActorFromCell(AActor* Actor, FVector2D Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->RemoveActorFromCell(Actor);
	}
}

// セル上のアクターにダメージ判定
void AGridManager::ExecuteAttackToGridCell(AActor* AttackedActor, float Damage, FVector2D Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->ExecuteAttackToActorOnCell(AttackedActor, Damage);
	}
}

// セル上のアクター情報更新
void AGridManager::RefleshActorInfoOnCell(AActor* MoveActor, FVector2D FromCoord, FVector2D ToCoord)
{
	if (MoveActor == nullptr)
		return;

	// 移動元のセルからアクター情報を除去
	if (AGridCellActor* FromCell = GetGridCellActor(FromCoord))
	{
		FromCell->RemoveActorFromCell(MoveActor);
	}

	// 移動先のセルにアクター情報を追加
	if (AGridCellActor* ToCell = GetGridCellActor(ToCoord))
	{
		ToCell->AddActorOnCell(MoveActor);
	}
}

// 攻撃予測を追加
void AGridManager::AddAttackSign(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		TargetCell->AddAttackSign();
	}
}

// 攻撃予測を除去
void AGridManager::RemoveAttackSign(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		TargetCell->RemoveAttackSign();
	}
}

// グリッド上に敵が存在するか
bool AGridManager::IsExistEnemyOnGrid()
{
	bool bIsExistEnemy = false;

	for (const auto& Col : Grid)
	{
		for (auto* Cell : Col)
		{
			if (Cell == nullptr)
				continue;

			// 敵がいる
			if (Cell->IsExistEnemyOnCell())
			{
				return true;
			}
		}
	}

	return false;
}

// グリッドマス上に敵が存在するか
bool AGridManager::IsExistEnemyOnGridCell(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->IsExistEnemyOnCell();
	}

	return false;
}

// グリッドセル上にいるエネミーを取得
AEnemyBase* AGridManager::GetEnemyOnGridCell(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->GetEnemyOnCell();
	}

	return nullptr;
}

// セル上にプレイヤーが存在するか
bool AGridManager::IsExistPlayerOnGridCell(FVector2D Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->IsExistPlayerOnCell();
	}

	return false;
}

// グリッド座標 → ワールド座標に変換
FVector AGridManager::ConvertToWorldPosition(FVector2D Coord)
{
	// 上方向がX軸のため、Coord.XとCoord.Yを逆に使用
	FVector Position = FVector(Coord.Y * GRID_CELL_UNIT * -1.f, Coord.X * GRID_CELL_UNIT, GRID_CELL_HEIGHT_UNIT * 0.5f);

	return Position;
}

// ワールド座標 → グリッド座標に変換
FVector2D AGridManager::ConvertToGridCoord(FVector Position)
{
	// 上方向がX軸のため、Coord.XとCoord.Yを逆に使用
	FVector2D Coord = FVector2D(Position.Y / GRID_CELL_UNIT, (Position.X * -1.f) / GRID_CELL_UNIT);

	return Coord;
}

// 二つの座標が 縦・横・斜め のいずれかの線上にいるか
bool AGridManager::IsSameLine(FVector2D Coord1, FVector2D Coord2)
{
	bool bIsSameLine = false;

	// 横
	bIsSameLine |= Coord1.X == Coord2.X;
	// 縦
	bIsSameLine |= Coord1.Y == Coord2.Y;
	// 斜め
	bIsSameLine |= FMath::Abs(Coord1.X + Coord1.Y) == FMath::Abs(Coord2.X + Coord2.Y);

	return bIsSameLine;
}

// プレイヤーと指定座標が同線上にいるか
bool AGridManager::IsPlayerSameLine(FVector2D Coord)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
		return false;
	APawn* Pawn = PlayerController->GetPawn();
	if (Pawn == nullptr)
		return false;

	// プレイヤーキャラクター情報にアクセス
	AMyCharacter* Player = Cast<AMyCharacter>(Pawn);
	if (Player)
	{
		return IsSameLine(Coord, Player->GetCurrentCoord());
	}

	return false;
}

// グリッド座標範囲外チェック
bool AGridManager::IsInGrid(FVector2D Coord)
{
	if (Coord.Y < 0 || Grid.Num() <= Coord.Y)
		return false;
	if (Coord.X < 0 || Grid[Coord.Y].Num() <= Coord.X)
		return false;

	return true;
}

// グリッドセルを取得
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

// グリッドサイズの取得
FVector2D AGridManager::GetGridSize()
{
	if (Grid.IsEmpty())
		return FVector2D::Zero();

	return FVector2D(Grid[0].Num(), Grid.Num());
}