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

    // ���̓����蔻��
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->OnComponentHit.AddDynamic(this, &ASimpleProjectile::OnHit);
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASimpleProjectile::OnOverlap);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    RootComponent = CollisionComp;

    // ���b�V��
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    // �ړ��R���|�[�l���g
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    // ���x�ɍ��킹�ĉ�]
    ProjectileMovement->bRotationFollowsVelocity = true;
    // �d�͂Ȃ�
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

// ���I�I�u�W�F�N�g�Ƃ̐ڐG
void ASimpleProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OverlappedComp == nullptr || OtherActor == nullptr || OtherActor == this || OtherComp == nullptr)
        return;

    // �v���C���[�͖���
    if (Cast<AMyCharacter>(OtherActor))
        return;

    // �_���[�W����
    if (AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor))
    {
        Enemy->OnTakeDamage(Damage);
    }

}

// �ÓI�I�u�W�F�N�g�Ƃ̐ڐG
void ASimpleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // �e����������
    if (OtherActor && OtherActor != this)
    {
        Destroy();
    }
}
