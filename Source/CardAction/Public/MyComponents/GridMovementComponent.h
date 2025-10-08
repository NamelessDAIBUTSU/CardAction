// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDACTION_API UGridMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridMovementComponent();

protected: /* UObject */
	virtual void BeginPlay() override;

public:	/* UActorComponent */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void MoveToDirection(FVector Direction);
	
	// グリッド移動
	UFUNCTION()
	void OnMoveToDirection(const FInputActionValue& Value);

	// 移動方向キャッシュの削除
	UFUNCTION()
	void OnResetDirectionCache(const FInputActionValue& Value);

	// 回転のみモードの変更
	UFUNCTION()
	void OnChangeTurnMode(const FInputActionValue& Value);

	// 座標
	FVector2D GetCurrentCoord() const { return CurrentCoord; }
	void SetCoord(FVector2D Coord) { CurrentCoord = Coord; }


private:
	// グリッド移動が終了したか
	bool IsFinishGridMove();

public:
	// 1移動のグリッド単位
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float GridUnit = 200.f;

private:
	// 回転だけのモードか
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	bool bIsTurningMode = false;

	// 移動中か
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	bool bIsMoving = false;

	// 移動方向のキャッシュ
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector DirectionCache = FVector::Zero();

	// グリッド移動用の移動量
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector MoveGridVector = FVector::Zero();
	// グリッド移動の移動先位置
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector TargetLocation = FVector::Zero();

	// 現在の座標
	FVector2D CurrentCoord = FVector2D::Zero();
};
