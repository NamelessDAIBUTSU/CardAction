// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PumpkinEnemy/PumpkinBomb.h"
#include <NiagaraFunctionLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"

APumpkinBomb::APumpkinBomb()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	if (SphereComp)
	{
		SphereComp->SetupAttachment(RootComponent);
		SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
		SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APumpkinBomb::OnHitGridCell);
	}
}

void APumpkinBomb::BeginPlay()
{
	Super::BeginPlay();
}

void APumpkinBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 到達判定
	ElapsedSec += DeltaTime;
	if (ElapsedSec > FallSec)
	{
		// 爆発エフェクト生成
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation() + FVector(0.f, 0.f, 100.f),
			FRotator::ZeroRotator,
			FVector(1.f),
			true
		);

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
		{
			AGridManager* GridManager = MyGameMode->GridManager;
			if (GridManager == nullptr)
				return;

			AGridCellActor* TargetCell = GridManager->GetGridCellActor(TargetPosition);
			if (TargetCell == nullptr)
				return;

			// 攻撃予測の除去
			GridManager->RemoveAttackSign(TargetCell->CellData.GridCoord);

			// ダメージ処理
			GridManager->ExecuteAttackToGridCell(this, Damage, TargetCell->CellData.GridCoord);
		}

		// 自身の削除
		Destroy();
		return;
	}

	// 移動
	FVector NewLocation;
	NewLocation.X = StartPosition.X + InitialVelocity.X * ElapsedSec;
	NewLocation.Y = StartPosition.Y + InitialVelocity.Y * ElapsedSec;
	NewLocation.Z = StartPosition.Z + InitialVelocity.Z * ElapsedSec - 0.5f * Gravity * ElapsedSec * ElapsedSec;
	SetActorLocation(NewLocation);
}

void APumpkinBomb::OnHitGridCell(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || OtherActor == this)
		return;

	// グリッドマネージャーに攻撃判定を追加
	
}

// 移動に必要なパラメータの設定
void APumpkinBomb::Setup(FVector Position) 
{ 
	StartPosition = GetActorLocation();
	TargetPosition = Position; 

	// 初速度の計算
	{
		// 目標地点と開始地点の距離
		FVector ToTarget = TargetPosition - StartPosition;

		// 距離に応じて落下速度を変更
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
		{
			AGridManager* GridManager = MyGameMode->GridManager;
			if (GridManager == nullptr)
				return;

			FCoord DistCell = GridManager->ConvertToGridCoord(TargetPosition) - GridManager->ConvertToGridCoord(StartPosition);
			FallSec *= DistCell.Vector2D().Size() * 0.5f;
		}

		// XY平面の速度
		// 1秒あたりの水平方向の速度を計算
		FVector HorizontalVelocity = ToTarget / FallSec;
		HorizontalVelocity.Z = 0.f;

		// Z方向の速度
		// 放物運動の公式 ： Z(t)  =  Start.Z + Vz(0) * t - 1/2 * g * t^2
		// 　　　　　　　 　 Vz(t) =  (Target.Z - Start.Z + 1/2 * g * t^2) / t
		float VerticalVelocity = (ToTarget.Z + 0.5f * Gravity * FallSec * FallSec) / FallSec;

		// 初速度
		InitialVelocity = FVector(HorizontalVelocity.X, HorizontalVelocity.Y, VerticalVelocity);
	}

}
