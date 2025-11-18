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
bool AGridManager::IsCellAccessible(FVector CheckPosition)
{
	FCoord Coord = ConvertToGridCoord(CheckPosition);
	return IsCellAccessible(Coord);
}
bool AGridManager::IsCellAccessible(FCoord Coord)
{
	AGridCellActor* GridCell = GetGridCellActor(Coord);
	if (GridCell == nullptr)
		return false;

	bool bIsAccessable = true;
	// 以下、条件判定
	// セル上にオブジェクトがあるならNG
	bIsAccessable &= GridCell->IsExistActorOnCell() == false;
	// 空セルはNG
	bIsAccessable &= GridCell->CellData.GridCellType != EGridCellType::None;
	// 移動先に指定されているセルはNG
	bIsAccessable &= GridCell->IsMoveTargetCell() == false;

	return bIsAccessable;
}

// エネミーをグリッド上にスポーン
void AGridManager::SpawnEnemies()
{
	if (GenerateGridData == nullptr)
		return;

	UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr || MapManager->GetCurrentStage() == nullptr)
		return;

	// スポーン可能な座標の取得
	TArray<FCoord> SpawnableCoords = GenerateGridData->EnemySpawnableCoords;

	// スポーンさせる敵の数を取得
	const int SpawnEnemyNum = GenerateGridData->SpawnEnemyNum;

	for (auto EnemyClass : MapManager->GetCurrentStage()->GetEnemyClassList())
	{
		if (SpawnableCoords.IsEmpty())
			break;

		// スポーンする位置を決定
		int RandomIndex = FMath::RandRange(0, SpawnableCoords.Num() - 1);
		FCoord SpawnCoord = SpawnableCoords[RandomIndex];
		FVector SpawnPosition = FVector(SpawnCoord.Y * GRID_CELL_UNIT * -1.f, SpawnCoord.X * GRID_CELL_UNIT, GRID_CELL_HEIGHT_UNIT * 0.5f);
		
		// スポーン
		AEnemyBase* NewEnemy = GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, SpawnPosition, FRotator(0.f, 180.f, 0.f));
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
void AGridManager::AddActorOnCell(AActor* Actor, FCoord Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->AddActorOnCell(Actor);
	}
}

// セル上から指定アクターの情報を削除
void AGridManager::RemoveActorFromCell(AActor* Actor, FCoord Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->RemoveActorFromCell(Actor);
	}
}

// セル上のアクターにダメージ判定
void AGridManager::ExecuteAttackToCell(AActor* AttackedActor, float Damage, FCoord Coord)
{
	if (IsInGrid(Coord) == false)
		return;

	if (Grid[Coord.Y][Coord.X])
	{
		Grid[Coord.Y][Coord.X]->ExecuteAttackToActorOnCell(AttackedActor, Damage);
	}
}

// セル上のアクター情報更新
void AGridManager::RefleshActorInfoOnCell(AActor* MoveActor, FCoord FromCoord, FCoord ToCoord)
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

// 移動先予定セルを登録/解除
void AGridManager::SetMoveTargetCell(FCoord Coord, bool Value)
{
	if (AGridCellActor* Cell = GetGridCellActor(Coord))
	{
		Cell->SetMoveTargetCell(Value);
	}
}

// 攻撃予測を追加
void AGridManager::AddAttackSign(FCoord Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		TargetCell->AddAttackSign();
	}
}

// 攻撃予測を除去
void AGridManager::RemoveAttackSign(FCoord Coord)
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
bool AGridManager::IsExistEnemyOnCell(FCoord Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->IsExistEnemyOnCell();
	}

	return false;
}

// セル上にプレイヤーが存在するか
bool AGridManager::IsExistPlayerOnCell(FCoord Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->IsExistPlayerOnCell();
	}

	return false;
}

// 空セルか
bool AGridManager::IsEmptyCell(FCoord Coord)
{
	if (AGridCellActor* TargetCell = GetGridCellActor(Coord))
	{
		return TargetCell->IsEmptyGridCell();
	}

	return false;
}

// 指定方向の次のセルが空のセル or グリッド外か
bool AGridManager::IsNextCellAccessible(FVector Dir, FCoord Coord)
{
	FCoord NextCoord = FCoord::Zero();

	// 縦方向
	if (FMath::IsNearlyZero(Dir.X) == false)
	{
		// 上
		if (Dir.X > 0)
		{
			NextCoord = FCoord(Coord.X, Coord.Y - 1);
		}
		// 下
		else
		{
			NextCoord = FCoord(Coord.X, Coord.Y + 1);
		}
	}
	// 横方向
	else if (FMath::IsNearlyZero(Dir.Y) == false)
	{
		// 右
		if (Dir.Y > 0)
		{
			NextCoord = FCoord(Coord.X + 1, Coord.Y);
		}
		// 左
		else
		{
			NextCoord = FCoord(Coord.X - 1, Coord.Y);
		}
	}

	// グリッド内 かつ 空セルじゃない
	if (AGridCellActor* TargetCell = GetGridCellActor(NextCoord))
	{
		return IsEmptyCell(NextCoord) == false;
	}

	return false;
}

// グリッド座標 → ワールド座標に変換
FVector AGridManager::ConvertToWorldPosition(FCoord Coord)
{
	// 上方向がX軸のため、Coord.XとCoord.Yを逆に使用
	FVector Position = FVector(Coord.Y * GRID_CELL_UNIT * -1.f, Coord.X * GRID_CELL_UNIT, GRID_CELL_HEIGHT_UNIT * 0.5f);

	return Position;
}

// ワールド座標 → グリッド座標に変換
FCoord AGridManager::ConvertToGridCoord(FVector Position)
{
	// 上方向がX軸のため、Coord.XとCoord.Yを逆に使用
	float X = Position.Y / GRID_CELL_UNIT;
	float Y = (Position.X * -1.f) / GRID_CELL_UNIT;
	int32 XCoord = FMath::RoundToInt(X);
	int32 YCoord = FMath::RoundToInt(Y);

	return FCoord(XCoord, YCoord);
}

// 二つの座標が 縦・横・斜め のいずれかの線上にいるか
bool AGridManager::IsSameLine(FCoord Coord1, FCoord Coord2)
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
bool AGridManager::IsPlayerSameLine(FCoord Coord)
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
bool AGridManager::IsInGrid(FCoord Coord)
{
	if (Coord.Y < 0 || Grid.Num() <= Coord.Y)
		return false;
	if (Coord.X < 0 || Grid[Coord.Y].Num() <= Coord.X)
		return false;

	return true;
}

// グリッドセルを取得
AGridCellActor* AGridManager::GetGridCellActor(FCoord Coord)
{
	if (IsInGrid(Coord) == false)
		return nullptr;

	return Grid[Coord.Y][Coord.X];
}
AGridCellActor* AGridManager::GetGridCellActor(FVector Position)
{
	FCoord Coord = ConvertToGridCoord(Position);
	return GetGridCellActor(Coord);
}

// グリッドサイズの取得
FVector2D AGridManager::GetGridSize()
{
	if (Grid.IsEmpty())
		return FVector2D::Zero();

	return FVector2D(Grid[0].Num(), Grid.Num());
}