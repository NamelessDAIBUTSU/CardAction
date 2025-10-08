// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PumpkinEnemy/PumpkinBomb.h"
#include <NiagaraFunctionLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "NiagaraSystem.h"

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

	// ���B����
	ElapsedSec += DeltaTime;
	if (ElapsedSec > FallSec)
	{
		// �����G�t�F�N�g����
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation() + FVector(0.f, 0.f, 125.f),
			FRotator::ZeroRotator,
			FVector(0.5f),
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

			// �U���\���̏���
			GridManager->RemoveAttackSign(TargetCell->CellData.GridCoord);

			// �_���[�W����
			GridManager->ExecuteAttackToGridCell(this, Damage, TargetCell->CellData.GridCoord);
		}

		// ���g�̍폜
		Destroy();
		return;
	}

	// �ړ�
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

	// �O���b�h�}�l�[�W���[�ɍU�������ǉ�
	
}

// �ړ��ɕK�v�ȃp�����[�^�̐ݒ�
void APumpkinBomb::Setup(FVector Position) 
{ 
	StartPosition = GetActorLocation();
	TargetPosition = Position; 

	// �����x�̌v�Z
	{
		// �ڕW�n�_�ƊJ�n�n�_�̋���
		FVector ToTarget = TargetPosition - StartPosition;

		// �����ɉ����ė������x��ύX
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
		{
			AGridManager* GridManager = MyGameMode->GridManager;
			if (GridManager == nullptr)
				return;

			FVector2D CellDist = GridManager->ConvertToGridCoord(TargetPosition) - GridManager->ConvertToGridCoord(StartPosition);
			FallSec *= CellDist.Size() * 0.5f;
		}

		// XY���ʂ̑��x
		// 1�b������̐��������̑��x���v�Z
		FVector HorizontalVelocity = ToTarget / FallSec;
		HorizontalVelocity.Z = 0.f;

		// Z�����̑��x
		// �����^���̌��� �F Z(t)  =  Start.Z + Vz(0) * t - 1/2 * g * t^2
		// �@�@�@�@�@�@�@ �@ Vz(t) =  (Target.Z - Start.Z + 1/2 * g * t^2) / t
		float VerticalVelocity = (ToTarget.Z + 0.5f * Gravity * FallSec * FallSec) / FallSec;

		// �����x
		InitialVelocity = FVector(HorizontalVelocity.X, HorizontalVelocity.Y, VerticalVelocity);
	}

}
