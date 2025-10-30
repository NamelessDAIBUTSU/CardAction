// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Grid/Cell/GridCellData.h"
#include "GridCellActor.generated.h"

UCLASS()
class CARDACTION_API AGridCellActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridCellActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;

public:
	// セル上のアクターを追加
	void AddActorOnCell(AActor* Actor);
	// セル上からアクターを除去
	void RemoveActorFromCell(AActor* Actor);

	// セル上にアクター存在するか
	bool IsExistActorOnCell();

	// マテリアル設定
	void ChangeDamageSignMaterial();
	void ChangeDefaultMaterial();

	// 枠マテリアル設定
	void ChangeEdgeMaterial(UMaterialInterface* Material);
	void ChangeEdgeDefaultMaterial();
	void ChangeEdgePlayerMaterial();
	void ChangeEdgeEnemyMaterial();

	// セル上のアクターにダメージ処理
	void ExecuteAttackToActorOnCell(AActor* AttackedActor, float Damage);

	// セル上に敵が存在するか
	bool IsExistEnemyOnCell();
	
	// セル上にプレイヤーが存在するか
	bool IsExistPlayerOnCell();

	// セル上のエネミーを取得
	class AEnemyBase* GetEnemyOnCell();

public: /* 攻撃予測 */
	// 攻撃予測の追加
	void AddAttackSign();
	// 攻撃予測の除去
	void RemoveAttackSign();

public:
	// スタティックメッシュ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;
	// 枠淵メッシュ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeLeftComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeRightComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeTopComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeDownComp;

	// 枠用マテリアル
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* EdgeDefaultMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* EdgePlayerMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* EdgeEnemyMaterial;

	// 攻撃との当たり判定用コリジョン
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* AttackCollisionComp = nullptr;

	// このセルが保持する情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	FGridCellData CellData;

private:
	// 攻撃予測のリクエストカウンタ
	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int AttackSignCount = 0;
};
