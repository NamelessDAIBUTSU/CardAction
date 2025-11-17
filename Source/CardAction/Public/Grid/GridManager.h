// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/Cell/GridCellActor.h"
#include "Grid/GridData.h"
#include <Enemy/EnemyBase.h>
#include "Util/CoordDef.h"
#include "GridManager.generated.h"

/// <summary>
/// グリッド空間の情報を管理するマネージャー
/// </summary>
UCLASS()
class CARDACTION_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridManager();

protected: /* UObject */
	virtual void BeginPlay() override;

public:	/* AActor */
	virtual void Tick(float DeltaTime) override;
	

public: /* 生成 */
	// 初期化
	void Initialize();

	// プレイヤーをスポーンさせるワールド座標取得
	FVector GetPlayerSpawnPosition();

public: /* セル関連処理 */
	// セル上にアクターを登録
	void AddActorOnCell(AActor* Actor, FCoord Coord);
	// セル上からアクターを除去
	void RemoveActorFromCell(AActor* Actor, FCoord Coord);

	// セル上のアクターにダメージ判定
	void ExecuteAttackToGridCell(AActor* AttackedActor, float Damage, FCoord Coord);

	// セル上のアクター情報更新
	void RefleshActorInfoOnCell(AActor* MoveActor, FCoord FromCoord, FCoord ToCoord);

	// 移動先予定セルを登録/解除
	void SetMoveTargetCell(FCoord Coord, bool Value);

public: /* 敵 */
	// 攻撃予測を追加
	void AddAttackSign(FCoord Coord);
	// 攻撃予測を除去
	void RemoveAttackSign(FCoord Coord);

	// グリッド上に敵が存在するか
	bool IsExistEnemyOnGrid();
	// グリッドマス上に敵が存在するか
	bool IsExistEnemyOnGridCell(FCoord Coord);

	// セル上にプレイヤーが存在するか
	bool IsExistPlayerOnGridCell(FCoord Coord);

	// 空セルか
	bool IsEmptyGridCell(FCoord Coord);

public: /* Util */
	// グリッド座標 → ワールド座標に変換
	FVector ConvertToWorldPosition(FCoord Coord);
	// ワールド座標 → グリッド座標に変換
	FCoord ConvertToGridCoord(FVector Position);

	// 二つの座標が 縦・横・斜め のいずれかの線上にいるか
	bool IsSameLine(FCoord Coord1, FCoord Coord2);
	// プレイヤーと指定座標が同線上にいるか
	bool IsPlayerSameLine(FCoord Coord);
	// アクセス可能なグリッドセルか
	bool IsAccessableGridCell(FVector CheckPosition);
	bool IsAccessableGridCell(FCoord Coord);

	// グリッドセルを取得
	AGridCellActor* GetGridCellActor(FCoord Coord);
	AGridCellActor* GetGridCellActor(FVector Position);

	// グリッドサイズの取得
	FVector2D GetGridSize();


private:
	// グリッド生成
	void GenerateGrid();
	// エネミーをグリッド上にスポーン
	void SpawnEnemies();

	// グリッド座標範囲外チェック
	bool IsInGrid(FCoord Coord);


public:
	// スポーンさせるエネミー情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<AEnemyBase>> SpawnEnemyArray;

private:
	// グリッド情報
	TArray<TArray<AGridCellActor*>> Grid;

	// 生成するグリッドデータ
	UPROPERTY()
	UGridData* GenerateGridData = nullptr;
};
