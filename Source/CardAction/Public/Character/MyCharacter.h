// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputAction.h>
#include <Weapon/WeaponBase.h>
#include <Card/CardData.h>
#include "MyComponents/GridMovementComponent.h"
#include "MyCharacter.generated.h"

UCLASS(Blueprintable)
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	// 入力バインド設定
	virtual void SetupPlayerInputComponent(UInputComponent* InputComp) override;


public: /* Callback */
	// 武器発動
	UFUNCTION()
	void OnUseWeapon(const FInputActionValue& Value);

	// アシスト発動
	UFUNCTION()
	void OnUseAssist(const FInputActionValue& Value);

	// ダメージ処理
	UFUNCTION()
	void OnTakeDamage(float Damage);

public:
	// 座標設定
	void SetCurrentCoord(FVector2D Coord);
	FVector2D GetCurrentCoord() const;

	// 武器を装備する
	void EquipWeapon(AWeaponActorBase* Weapon);
	// 現在武器を装備中か
	bool IsEquippedWeapon() { return EquippedWeapon != nullptr; }

	// ゲッタ
	UGridMovementComponent* GetGridMovementComponent() { return GridMovementComp; }


public: /* Input */
	// 武器発動
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UseWeaponAction = nullptr;

	// アシスト発動
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UseAssistAction = nullptr;

	// グリッド移動
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveGridAction = nullptr;

	// 回転モード
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* TurnTowardAction = nullptr;


public: /* Status */
	// HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 CurrentHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 MaxHP = 100;
	// エナジー
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 CurrentEnergy = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 MaxEnergy = 10;


public: /* 武器 */
	// マズルオフセット
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	FVector MazzleOffset = FVector(0.f, 0.f, 50.f);

	// 装備武器
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeaponActorBase* EquippedWeapon = nullptr;


public: /* カード */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UCardData* DefaultCardData = nullptr;


private: /* Component */
	// グリッド移動コンポーネント
	class UGridMovementComponent* GridMovementComp = nullptr;

private:
	// 座標
	FVector2D CurrentCoord = FVector2D::Zero();
};

