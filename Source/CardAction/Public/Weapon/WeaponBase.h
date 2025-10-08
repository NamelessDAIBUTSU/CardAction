// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AWeaponActorBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponActorBase();
	~AWeaponActorBase();

public:
	// プレイヤーによる攻撃アクション時
	virtual void OnAttack() PURE_VIRTUAL(OnAttack,);

	// 所有者の設定
	void SetOwner(class AMyCharacter* Player) { WeaponOwner = Player; }


public: /* Status */
	// ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int Damage = 0;

	// クールダウン
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float CoolTime = 0.f;

	// 制限時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float LimitSec = 0.f;

public: /* Component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshComp = nullptr;

protected:
	UPROPERTY(VisibleAnywhere)
	AMyCharacter* WeaponOwner = nullptr;
};
