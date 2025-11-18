// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon_ThrowKnife.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"
#include "Util/CoordDef.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyManager.h"

AWeapon_ThrowKnife::AWeapon_ThrowKnife()
{
    // 移動コンポーネント生成
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Move Comp"));
	if (ProjectileMoveComp)
	{
        ProjectileMoveComp->InitialSpeed = Verocity;
        ProjectileMoveComp->Velocity = GetActorForwardVector() * Verocity;

        ProjectileMoveComp->MaxSpeed = Verocity;
        // 速度に合わせて回転しない
        ProjectileMoveComp->bRotationFollowsVelocity = false;
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

        SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_ThrowKnife::OnOverlap);
    }
}

void AWeapon_ThrowKnife::Tick(float DeltaSec)
{
    // 進行方向を軸に回転
    Super::Tick(DeltaSec);
}

void AWeapon_ThrowKnife::OnOverlap(UPrimitiveComponent* OverlappedComp,
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
    // 敵が死亡モーション中なら消さない
    if (AEnemyBase* Enemy = EnemyManager->GetEnemy(Coord))
    {
        bIsExistEnemyOnGridCell &= (Enemy->IsPlayingDeadMontage() == false);
    }

    // ダメージ判定追加
    GridManager->ExecuteAttackToCell(this, Damage, Coord);

    // 敵マスの場合、自身の削除
    if (bIsExistEnemyOnGridCell)
    {
        Destroy();
    }
}

void AWeapon_ThrowKnife::BeginPlay()
{
    Super::BeginPlay();
}
