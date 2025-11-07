// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Util/CoordDef.h>
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

public: /* プレイヤー用 */
	// グリッド移動
	UFUNCTION()
	void OnMoveToDirection(const FInputActionValue& Value);

	// 移動方向キャッシュの削除
	UFUNCTION()
	void OnResetDirectionCache(const FInputActionValue& Value);

	// 回転のみモードの変更
	UFUNCTION()
	void OnChangeTurnMode(const FInputActionValue& Value);

public:
	// 移動リクエスト
	void RequestMoveToDirection(FCoord Coord, float GoalSecond);

	// 座標
	UFUNCTION()
	FCoord GetCurrentCoord() const { return CurrentCoord; }
	void SetCoord(FCoord Coord) { CurrentCoord = Coord; }

	// 移動中
	UFUNCTION(BlueprintCallable)
	bool IsMoving() const { return bIsMoving; }

private:
	// グリッド移動が終了したか
	bool IsFinishGridMove();

	// 移動更新
	void UpdateGridMove(float DeltaSec);


private: /* プレイヤー用 */
	// 連続移動制御用の移動方向キャッシュ
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector2D DirectionCache = FVector2D::Zero();

private:
	// 回転だけのモードか
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	bool bIsTurningMode = false;

	// 現在の座標
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FCoord CurrentCoord = FCoord::Zero();

private: /* 移動更新関連 */
	// 移動中か
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	bool bIsMoving = false;

	// 1秒の移動量
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector MoveSpeed = FVector::Zero();

	// 移動先位置
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector TargetLocation = FVector::Zero();
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FCoord TargetCoord = FCoord::Zero();

	// 1フレーム前の座標
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FCoord CoordCache = FCoord::Zero();

	// 移動時間
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	float GoalSec = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	float ElapsedSec = 0.f;
};
