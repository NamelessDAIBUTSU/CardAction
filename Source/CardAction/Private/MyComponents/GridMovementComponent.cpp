// Fill out your copyright notice in the Description page of Project Settings.


#include "MyComponents/GridMovementComponent.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

// Sets default values for this component's properties
UGridMovementComponent::UGridMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGridMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGridMovementComponent::MoveToDirection(FVector Direction)
{
	AActor* Owner = GetOwner();
	if (Owner == nullptr)
		return;

	APawn* PawnOwner = Cast<APawn>(Owner);
	if (PawnOwner == nullptr)
		return;

	AController* Controller = PawnOwner->GetController();
	if (Controller == nullptr)
		return;

	// 移動中は移動終了判定のみ
	if (IsFinishGridMove() == false)
		return;

	// コントローラのYaw回転を取得
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// 前方向/右方向を取得
	const FVector UpDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// ワールド軸に合わせて進行方向用のベクトルを作成
	// #MEMO : 上方向がX軸、右方向がY軸のため、Direction(1.f, 0.f)ならRightDirectionを使用
	FVector MoveDirection;
	if (Direction.X != 0.f)
	{
		MoveDirection = RightDirection * Direction.X;
	}
	else if (Direction.Y != 0.f)
	{
		MoveDirection = UpDirection * Direction.Y;
	}

	// 到着地点を計算
	TargetLocation = Owner->GetActorLocation() + MoveDirection * GridUnit;

	// 前回の進行方向と同じであれば抜ける
	if (DirectionCache.Equals(MoveDirection))
		return;

	// 進行方向に回転
	FRotator NextRotation = (TargetLocation - Owner->GetActorLocation()).Rotation();
	Owner->SetActorRotation(NextRotation);

	// 向き変更フラグが立っていないなら、グリッド移動
	if (bIsTurningMode == false)
	{
		if (AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this))
		{
			if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
			{
				auto* GridManager = MyGameMode->GridManager;
				if (GridManager == nullptr)
					return;

				// 進行方向のグリッドが進行可能状態か
				if (GridManager->IsAccessableGridCell(TargetLocation) == false)
				{
					return;
				}

				// 移動中フラグを立てる
				bIsMoving = true;

				// グリッドマネージャーのアクターの位置情報を更新
				FVector2D FromCell = GridManager->ConvertToGridCoord(Owner->GetActorLocation());
				FVector2D ToCell = GridManager->ConvertToGridCoord(TargetLocation);
				GridManager->RefleshActorInfoOnCell(Owner, FromCell, ToCell);

				// 位置設定
				Owner->SetActorLocation(TargetLocation);

				// 座標設定
				SetCoord(ToCell);
			}
		}
	}

	// キャッシュの更新
	DirectionCache = MoveDirection;
}

void UGridMovementComponent::OnMoveToDirection(const FInputActionValue& Value)
{
	// 移動中は移動終了判定のみ
	if (IsFinishGridMove() == false)
		return;

	// 移動量の取得
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// 進行方向の取得
	FVector2D Dir;
	if (FMath::Abs(MovementVector.X) < FMath::Abs(MovementVector.Y))
	{
		Dir = FVector2D(0.f, MovementVector.Y);
	}
	if (FMath::Abs(MovementVector.X) >= FMath::Abs(MovementVector.Y))
	{
		Dir = FVector2D(MovementVector.X, 0.f);
	}
	// 正規化
	Dir = Dir.GetSafeNormal();

	MoveToDirection(FVector(Dir.X, Dir.Y, 0.f));
}

// 移動方向キャッシュの削除
void UGridMovementComponent::OnResetDirectionCache(const FInputActionValue& Value)
{
	DirectionCache = FVector::Zero();
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
		bIsMoving = false;
		return true;
	}
	// 移動中
	else
	{
		return false;
	}
}


