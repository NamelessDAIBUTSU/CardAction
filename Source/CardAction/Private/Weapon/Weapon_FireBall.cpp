// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon_FireBall.h"
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Grid/GridManager.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Util/CoordDef.h"
#include "Components/SphereComponent.h"
#include "Enemy/EnemyManager.h"

AWeapon_FireBall::AWeapon_FireBall()
{
    PrimaryActorTick.bCanEverTick = true;

    // コンポーネント作成
    ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
    if (ParticleComp)
    {
        ParticleComp->SetupAttachment(RootComponent);
        ParticleComp->bAutoActivate = true;
    }

    // 移動コンポーネント生成
    ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Move Comp"));
    if (ProjectileMoveComp)
    {
        ProjectileMoveComp->Velocity = GetActorForwardVector() * ProjectileMoveComp->InitialSpeed;
        // 重力なし
        ProjectileMoveComp->ProjectileGravityScale = 0.f;
    }

    // 当たり判定コンポーネント生成
    SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
    if (SphereCollisionComp)
    {
        SphereCollisionComp->SetupAttachment(MeshComp);
        SphereCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        SphereCollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
        SphereCollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

        SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_FireBall::OnOverlap);
    }
}

void AWeapon_FireBall::Tick(float DeltaSec)
{
    Super::Tick(DeltaSec);

    // 加速処理
    if (ProjectileMoveComp)
    {
        if (FMath::IsNearlyEqual(ProjectileMoveComp->InitialSpeed, ProjectileMoveComp->MaxSpeed) == false)
        {
            if (ProjectileMoveComp)
            {
                FVector CurrentVel = ProjectileMoveComp->Velocity;
                float Speed = CurrentVel.Size();

                if (Speed < ProjectileMoveComp->MaxSpeed)
                {
                    float NewSpeed = FMath::Min(Speed + AccelRate * DeltaSec, ProjectileMoveComp->MaxSpeed);
                    ProjectileMoveComp->Velocity = CurrentVel.GetSafeNormal() * NewSpeed;
                }
            }
        }
    }
}

void AWeapon_FireBall::BeginPlay()
{
    Super::BeginPlay();

    // 発射エフェクト再生
    UGameplayStatics::SpawnEmitterAtLocation(
        GetWorld(),
        ShockWaveEffect,
        GetActorLocation(),
        FRotator::ZeroRotator,
        FVector(1.0f),
        true
    );

    // 本体のエフェクト再生
    if (ParticleComp && BodyEffect)
    {
        ParticleComp->SetTemplate(BodyEffect);
        ParticleComp->ActivateSystem(true);
    }

    // InitialSpeedが設定されてから速度設定
    if (ProjectileMoveComp)
    {
        ProjectileMoveComp->Velocity = GetActorForwardVector() * ProjectileMoveComp->InitialSpeed;
        // 重力なし
        ProjectileMoveComp->ProjectileGravityScale = 0.f;
    }
}


void AWeapon_FireBall::OnOverlap(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor == nullptr)
        return;

    AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGM == nullptr)
        return;

    AGridManager* GridManager = MyGM->GridManager;
    if (GridManager == nullptr)
        return;

    AEnemyManager* EnemyManager = MyGM->EnemyManager;
    if (EnemyManager == nullptr)
        return;

    // 発射位置のグリッドマスとの当たり判定は無視
    FCoord Coord = GridManager->ConvertToGridCoord(OtherActor->GetActorLocation());
    if (Coord == SpawnCoord)
        return;


    // 敵がいるマスか先に取得しておく
    bool bIsExistEnemyOnGridCell = GridManager->IsExistEnemyOnCell(Coord);

    // 敵が死亡モーション中なら当たり判定を取らない
    if (AEnemyBase* Enemy = EnemyManager->GetEnemy(Coord))
    {
        bIsExistEnemyOnGridCell &= (Enemy->IsPlayingDeadMontage() == false);
    }

    // ダメージ処理
    GridManager->ExecuteAttackToCell(this, Damage, Coord);

    // 敵マスの場合、自身の削除
    if (bIsExistEnemyOnGridCell)
    {
        // ヒットエフェクト再生
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            HitEffect,
            GetActorLocation(),
            FRotator::ZeroRotator,
            FVector(1.0f),
            true
        );

        Destroy();
    }
}