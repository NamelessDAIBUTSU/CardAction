// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Util/CoordDef.h"
#include "EnemyAttackBase.generated.h"

/// <summary>
/// 敵の攻撃クラスの基本クラス
/// </summary>
UCLASS(abstract)
class CARDACTION_API AEnemyAttackBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyAttackBase();

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	void SetCurrentCoord(FCoord Coord) { CurrentCoord = Coord; }
	FCoord GetCurrentCoord() const { return CurrentCoord; }


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 Damage = 0;

	// 見た目
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

protected:
	// 攻撃が有効か
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsValidAttack = true;

	// 座標
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCoord CurrentCoord = FCoord::Zero();
};
