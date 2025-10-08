// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/Cell/GridCellActor.h"
#include "Grid/GridData.h"
#include <Enemy/EnemyBase.h>
#include "GridManager.generated.h"

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
	// グリッド生成
	void GenerateGrid(UGridData* GridData);
	// エネミーをグリッド上にスポーン
	void SpawnEnemies();
	// プレイヤーをスポーンさせるワールド座標取得
	FVector GetPlayerSpawnPosition();

public: /* セル関連処理 */
	// セル上にアクターを登録
	void AddActorOnCell(AActor* Actor, FVector2D Coord);
	// セル上からアクターを除去
	void RemoveActorFromGrid(AActor* Actor, FVector2D Coord);

	// セル上のアクターにダメージ判定
	void ExecuteAttackToGridCell(AActor* AttackedActor, float Damage, FVector2D Coord);

	// セル上のアクター情報更新
	void RefleshActorInfoOnCell(AActor* MoveActor, FVector2D FromCoord, FVector2D ToCoord);

public: /* 敵 */
	// 攻撃予測を追加
	void AddAttackSign(FVector2D Coord);
	// 攻撃予測を除去
	void RemoveAttackSign(FVector2D Coord);

	// グリッド上に敵が存在するか
	bool IsExistEnemyOnGrid();

public: /* Util */
	// グリッド座標 → ワールド座標に変換
	FVector ConvertToWorldPosition(FVector2D Coord);
	// ワールド座標 → グリッド座標に変換
	FVector2D ConvertToGridCoord(FVector Position);

	// 二つの座標が 縦・横・斜め のいずれかの線上にいるか
	bool IsSameLine(FVector2D Coord1, FVector2D Coord2);
	// プレイヤーと指定座標が同線上にいるか
	bool IsPlayerSameLine(FVector2D Coord);
	// アクセス可能なグリッドセルか
	bool IsAccessableGridCell(FVector CheckPosition);

	// グリッドセルを取得
	AGridCellActor* GetGridCellActor(FVector2D Coord);
	AGridCellActor* GetGridCellActor(FVector Position);

	// グリッドサイズの取得
	FVector2D GetGridSize();

private:
	// グリッド座標範囲外チェック
	bool IsInGrid(FVector2D Coord);


public:
	// 生成するグリッドデータ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UGridData* GenerateGridData = nullptr;

	// スポーンさせるエネミー情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<AEnemyBase>> SpawnEnemyArray;

private:
	// グリッド情報
	TArray<TArray<AGridCellActor*>> Grid;
};
