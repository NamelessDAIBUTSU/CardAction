// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/WidgetComponent.h>
#include "Delegates/DelegateCombinations.h"
#include <MyComponents/GridMovementComponent.h>
#include "EnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDead, AEnemyBase*, DeadEnemy);

UCLASS()
class CARDACTION_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: /* Callback */
	UFUNCTION()
	void OnTakeDamage(int TakeDamage);

	// 死亡時のコールバック
	UFUNCTION()
	virtual void OnDead();

public:
	// 回転可能か
	virtual bool CanRotate() { return true; }

	// 座標
	void SetCurrentCoord(FVector2D Coord);
	FVector2D GetCurrentCoord() const;

	// グリッド移動コンポーネント
	UGridMovementComponent* GetGridMovementComponent() { return GridMovementComp; }


private:
	// HPバーの更新
	void UpdateHPBarWidget();
	// プレイヤーの方向を向く
	void LookAtPlayer();


public: /* Status */
	// ダメージ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int Damage = 0;
	// 体力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int CurrentHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int MaxHP = 100;

	// 自動でプレイヤーの方向を向くか
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsAutoLookAtPlayer = true;

public: /* Anim */
	// 登場アニメーションを再生したか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	bool bIsPlayedEntryAnim = false;

public: /* Callback */
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnEnemyDead OnEnemyDied;

public: /* Component */
	// HPバー
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UWidgetComponent* WidgetComp = nullptr;


protected: /* Component */
	// グリッド移動
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UGridMovementComponent* GridMovementComp = nullptr;
};
