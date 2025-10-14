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
	virtual void OnAttack() {};

	// 所有者の設定
	void SetWeaponOwner(class AMyCharacter* Player) { WeaponOwner = Player; }


public: /* Status */
	// ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int Damage = 0;
	// クールダウン
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float CoolTime = 0.f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshComp = nullptr;

	// 攻撃時に再生するプレイヤーのモンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* AttackMontage = nullptr;

protected:
	UPROPERTY(VisibleAnywhere)
	AMyCharacter* WeaponOwner = nullptr;
};
