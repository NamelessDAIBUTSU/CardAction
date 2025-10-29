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
	virtual void BeginDestroy() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: /* Callback */
	UFUNCTION()
	void OnTakeDamage(int TakeDamage);

	// 死亡時のコールバック
	UFUNCTION()
	virtual void OnBeforeDead();

public: /* AI */
	void SetCanMove(bool Value) { bCanMove = Value; }
	bool CanMove() const { return bCanMove; }

	void SetMoveCount(int Count) { MoveCount = Count; }
	int GetMoveCount() { return MoveCount; }

public:
	// 回転可能か
	virtual bool CanRotate() { return true; }

	// 座標
	void SetCurrentCoord(FVector2D Coord);
	FVector2D GetCurrentCoord() const;

	// グリッド移動コンポーネント
	UGridMovementComponent* GetGridMovementComponent() { return GridMovementComp; }

	// 死亡モンタージュ終了後処理
	void OnEndDeadMontage(UAnimMontage* Montage, bool bInterrupted);
	// 死んだか
	bool IsDead() const { return bIsDead; }
	// 死亡モンタージュ再生中か
	bool IsPlayingDeadMontage();

	// 開始準備ができているか
	bool IsReady() const { return bIsReady; }
	void SetIsReady(bool IsReady) { bIsReady = IsReady; }

private:
	// プレイヤーの方向を向く
	void LookAtPlayer();
	// 自身の削除
	void SelfDestroy();


public: /* Info */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FString Description;

public: /* Status */
	// 体力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int CurrentHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int MaxHP = 100;

	// 自動でプレイヤーの方向を向くか
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsAutoLookAtPlayer = true;

public: /* AI */
	// 何回の移動で攻撃をするか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int AttackSpan = 0;

public: /* UI */
	// アイコン画像
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UTexture2D* IconTexture = nullptr;

public: /* Anim */
	// 死亡モンタージュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* DeadAnimMontage = nullptr;

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

protected: /* AI */
	// 現在の移動回数
	UPROPERTY(VisibleAnywhere, Category = "AI")
	int MoveCount = 0;
	// 移動可能か
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bCanMove = true;

protected:
	// 死んだか
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsDead = false;

	// 開始準備ができたか
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsReady = false;
};
