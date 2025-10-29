#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include <Enemy/EnemyAttackBase.h>
#include "CactusEnemy.generated.h"

UCLASS()
class CARDACTION_API ACactusEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	ACactusEnemy() {};

protected:
	virtual void BeginPlay() override;

public:
	// プレイヤーへの回転はしない
	virtual bool CanRotate() override { return false; }

public:
	// 生成するカクタスニードル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<AEnemyAttackBase> AttackClass;
};
