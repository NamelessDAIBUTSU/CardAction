// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon_ThrowKnife.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"

AWeapon_ThrowKnife::AWeapon_ThrowKnife()
{
    // �ړ��R���|�[�l���g����
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Move Comp"));
	if (ProjectileMoveComp)
	{
        ProjectileMoveComp->InitialSpeed = Verocity;
        ProjectileMoveComp->Velocity = GetActorForwardVector() * Verocity;

        ProjectileMoveComp->MaxSpeed = Verocity;
        // ���x�ɍ��킹�ĉ�]���Ȃ�
        ProjectileMoveComp->bRotationFollowsVelocity = false;
        // �d�͂Ȃ�
        ProjectileMoveComp->ProjectileGravityScale = 0.f;
	}

    // �����蔻��R���|�[�l���g����
    SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
    if (SphereCollisionComp)
    {
        SphereCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        SphereCollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
        SphereCollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

        SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_ThrowKnife::OnOverlap);
    }

    // �������̍��W��ۑ�
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
    // �i�s���������ɉ�]
    
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

    // ���ˈʒu�̃O���b�h�}�X�Ƃ̓����蔻��͖���
    AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
    if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
    {
        if (MyGM->GridManager == nullptr)
            return;

        FVector2D Coord = MyGM->GridManager->ConvertToGridCoord(OtherActor->GetActorLocation());
        if (Coord == GeneratedCoord)
            return;
    }

    // ���g�̍폜
    Destroy();
}
