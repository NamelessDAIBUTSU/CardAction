// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon_ThrowKnife.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"

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
        SphereCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        SphereCollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
        SphereCollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

        SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_ThrowKnife::OnOverlap);
    }

    // 生成時の座標を保存
    AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
    if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
    {
        if (MyGM->GridManager == nullptr)
            return;

        GeneratedCoord = MyGM->GridManager->ConvertToGridCoord(GetActorLocation());
    }
}

void AWeapon_ThrowKnife::Tick(float DeltaSec)
{
    // 進行方向を軸に回転
    
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

    // 発射位置のグリッドマスとの当たり判定は無視
    AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
    if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
    {
        if (MyGM->GridManager == nullptr)
            return;

        FVector2D Coord = MyGM->GridManager->ConvertToGridCoord(OtherActor->GetActorLocation());
        if (Coord == GeneratedCoord)
            return;
    }

    // 自身の削除
    Destroy();
}
