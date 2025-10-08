// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SimpleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Character/MyCharacter.h>
#include <Enemy/EnemyBase.h>

// Sets default values
ASimpleProjectile::ASimpleProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 球の当たり判定
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->OnComponentHit.AddDynamic(this, &ASimpleProjectile::OnHit);
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASimpleProjectile::OnOverlap);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    RootComponent = CollisionComp;

    // メッシュ
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    // 移動コンポーネント
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    // 速度に合わせて回転
    ProjectileMovement->bRotationFollowsVelocity = true;
    // 重力なし
    ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void ASimpleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 動的オブジェクトとの接触
void ASimpleProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OverlappedComp == nullptr || OtherActor == nullptr || OtherActor == this || OtherComp == nullptr)
        return;

    // プレイヤーは無視
    if (Cast<AMyCharacter>(OtherActor))
        return;

    // ダメージ判定
    if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
    {
        Enemy->OnTakeDamage(Damage);
    }

}

// 静的オブジェクトとの接触
void ASimpleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 弾を消すだけ
    if (OtherActor && OtherActor != this)
    {
        Destroy();
    }
}
