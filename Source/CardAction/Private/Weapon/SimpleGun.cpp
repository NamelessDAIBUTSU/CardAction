// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SimpleGun.h"
#include <Character/MyCharacter.h>
#include "Projectile/SimpleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ASimpleGun::OnAttack()
{
    if (GetWorld() == nullptr || WeaponOwner == nullptr || BPProjectile == nullptr)
        return;

    // �ˏo���v���C���[���ʕ����ɐݒ�
    FVector MuzzleLocation = WeaponOwner->GetActorLocation() + WeaponOwner->GetActorForwardVector() * 100.f + WeaponOwner->MazzleOffset;

    // �����ɕK�v�ȏ���ݒ�
    // ���ˌ����v���C���[�̒��S������ɐݒ�
    FVector PlayerCenterLocation = WeaponOwner->GetActorLocation() + WeaponOwner->MazzleOffset;
    // �����x���ˏo�����ɂ���
    FVector LaunchDir = (MuzzleLocation - PlayerCenterLocation).GetSafeNormal();
    // �ˏo�����ւ̉�]
    FRotator MuzzleRotation = LaunchDir.Rotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = WeaponOwner;
    SpawnParams.Instigator = WeaponOwner->GetInstigator();
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // �e�̐���
    ASimpleProjectile* Projectile = GetWorld()->SpawnActor<ASimpleProjectile>(
        BPProjectile,
        MuzzleLocation,
        MuzzleRotation,
        SpawnParams
    );

    if (Projectile)
    {
        // �����̐ݒ�
        Projectile->ProjectileMovement->Velocity = LaunchDir * Projectile->ProjectileMovement->InitialSpeed;
        // �_���[�W�̐ݒ�
        Projectile->Damage = Damage;
    }
}
