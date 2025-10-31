// Fill out your copyright notice in the Description page of Project Settings.


#include "MyComponents/GridMovementComponent.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Grid\GridManager.h"

UGridMovementComponent::UGridMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGridMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 線形移動更新
	UpdateGridMove(DeltaTime);
}

// 移動リクエスト
void UGridMovementComponent::RequestMoveToDirection(FVector2D TargetCoord, float GoalSecond)
{
	// 移動中はリクエストできない
	if (bIsMoving)
		return;

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では処理をしない
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
		return;

	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (PawnOwner == nullptr)
		return;

	AController* Controller = PawnOwner->GetController();
	if (Controller == nullptr)
		return;

	AGridManager* GridManager = MyGameMode->GridManager;
	if (GridManager == nullptr)
		return;


	// コントローラのYaw回転を取得
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// 前方向/右方向を取得
	const FVector UpDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 到着地点を取得
	TargetLocation = GridManager->ConvertToWorldPosition(TargetCoord);
	TargetLocation.Z = PawnOwner->GetActorLocation().Z;

	// 進行方向に回転
	FVector Dist = TargetLocation - PawnOwner->GetActorLocation();
	FRotator NextRotation = Dist.Rotation();
	NextRotation.Pitch = 0.f;
	PawnOwner->SetActorRotation(NextRotation);

	// 向き変更フラグが立っていないなら、グリッド移動
	if (bIsTurningMode == false)
	{
		// 進行方向のグリッドが進行可能状態か
		if (GridManager->IsAccessableGridCell(TargetLocation) == false)
		{
			return;
		}

		// 毎フレームの移動量を保存
		GoalSec = GoalSecond;
		if (FMath::IsNearlyZero(GoalSec))
		{
			MoveSpeed = Dist;
		}
		else
		{
			MoveSpeed = Dist / GoalSec;
		}

		// 移動終了後に元の位置をグリッドマネージャーから除去するための座標保存
		FromCoord = GridManager->ConvertToGridCoord(PawnOwner->GetActorLocation());
		GridManager->RemoveActorFromCell(PawnOwner, FromCoord);

		// ほかのアクターと移動先が被らないように、移動先の座標登録
		FVector2D ToCoord = GridManager->ConvertToGridCoord(TargetLocation);
		GridManager->AddActorOnCell(PawnOwner, ToCoord);

		// 更新用の変数をリセット
		ElapsedSec = 0.f;

		// 移動中フラグを立てる
		bIsMoving = true;
	}
}

void UGridMovementComponent::OnMoveToDirection(const FInputActionValue& Value)
{
	// 移動中は移動終了判定のみ
	if (IsFinishGridMove() == false)
		return;

	// 移動量の取得
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// 長押しによる高速移動制御
	if (DirectionCache.Equals(MovementVector))
		return;

	// 移動方向のキャッシュ
	DirectionCache = MovementVector;

	// 進行方向の取得
	FVector2D Dir;
	if (FMath::Abs(MovementVector.X) < FMath::Abs(MovementVector.Y))
	{
		Dir = FVector2D(0.f, MovementVector.Y * -1.f);
	}
	if (FMath::Abs(MovementVector.X) >= FMath::Abs(MovementVector.Y))
	{
		Dir = FVector2D(MovementVector.X, 0.f);
	}
	// 正規化
	Dir = Dir.GetSafeNormal();

	// 移動リクエスト
	FVector2D TargetCoord = CurrentCoord + Dir;
	RequestMoveToDirection(TargetCoord, 0.1f);
}

// 移動方向キャッシュの削除
void UGridMovementComponent::OnResetDirectionCache(const FInputActionValue& Value)
{
	DirectionCache = FVector2D::Zero();
}

void UGridMovementComponent::OnChangeTurnMode(const FInputActionValue& Value)
{
	// 向きだけ変更するフラグを更新
	bIsTurningMode = Value.Get<bool>();
}

// グリッド移動が終了したか
bool UGridMovementComponent::IsFinishGridMove()
{
	// 移動中じゃない
	if (bIsMoving == false)
		return true;

	AActor* Owner = GetOwner();
	if (Owner == nullptr)
		return true;

	// 移動終了
	if (TargetLocation.Equals(Owner->GetActorLocation()))
	{
		return true;
	}

	// 移動中
	return false;
}

// 移動更新
void UGridMovementComponent::UpdateGridMove(float DeltaSec)
{
	if (bIsMoving == false)
		return;

	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (PawnOwner == nullptr)
		return;

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode == nullptr)
		return;

	AGridManager* GridManager = MyGameMode->GridManager;
	if (GridManager == nullptr)
		return;


	// 移動
	FVector CurrentLocation = PawnOwner->GetActorLocation();
	CurrentLocation += MoveSpeed * DeltaSec;
	
	// 移動補正
	ElapsedSec += DeltaSec;
	if (ElapsedSec >= GoalSec)
	{
		CurrentLocation = TargetLocation;
	}
	PawnOwner->SetActorLocation(CurrentLocation);

	// 現在の座標を更新
	SetCoord(GridManager->ConvertToGridCoord(CurrentLocation));

	// 移動が終了したら
	if (IsFinishGridMove())
	{
		// フラグを降ろす
		bIsMoving = false;

		// グリッドマネージャーの元の座標から自身を除去
		GridManager->RemoveActorFromCell(PawnOwner, FromCoord);
	}
}


