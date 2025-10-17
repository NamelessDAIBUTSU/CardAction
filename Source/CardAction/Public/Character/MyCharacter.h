// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputAction.h>
#include <Weapon/WeaponBase.h>
#include <Card/CardData.h>
#include "MyComponents/GridMovementComponent.h"
#include <Components/WidgetComponent.h>
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
	void OnUseCard(const FInputActionValue& Value);

	// カード選択
	UFUNCTION()
	void OnSelectFirstCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnSelectSecondCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnSelectThirdCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnSelectFourthCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnScrollSelectCard(const FInputActionValue& Value);

	// ダメージ処理
	UFUNCTION()
	void OnTakeDamage(float Damage);

public:
	// 座標設定
	void SetCurrentCoord(FVector2D Coord);
	FVector2D GetCurrentCoord() const;

	// ゲッタ
	UGridMovementComponent* GetGridMovementComponent() { return GridMovementComp; }

	// 手札にカードを追加
	void AddToHandCards(UCardData* CardData);
	// 手札からカードを除去
	void RemoveFromHandCards(UCardData* CardData);

private:
	// 手札ウィジェットに反映
	void RefleshHandCards();

public: /* Input */
	// カード発動
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UseCardAction = nullptr;

	// 手札の選択
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectFirstCardAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectSecondCardAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectThirdCardAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectFourthCardAction = nullptr;
	// 手札の選択（ホイールスクロール）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ScrollSelectCardAction = nullptr;

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


private:
	// 手札カード
	UPROPERTY(VisibleAnywhere, Category = "Card")
	TArray<UCardData*> HandCards;
	// 手札の選択中インデックス
	UPROPERTY(VisibleAnywhere, Category = "Card")
	int SelectHandCardsIndex = 0;

	// グリッド移動コンポーネント
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UGridMovementComponent* GridMovementComp = nullptr;
	// HPバー用コンポーネント
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UWidgetComponent* WidgetComp = nullptr;
};

