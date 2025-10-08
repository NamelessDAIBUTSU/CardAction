// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAttackBase.generated.h"

UCLASS(abstract)
class CARDACTION_API AEnemyAttackBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyAttackBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 Damage = 0;

	// å©ÇΩñ⁄
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

protected:
	// çUåÇÇ™óLå¯Ç©
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsValidAttack = true;

	// ç¿ïW
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D CurrentCoord = FVector2D::Zero();
};
