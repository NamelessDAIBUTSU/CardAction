// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SimpleGun.h"
#include <Character/MyCharacter.h>
#include "Projectile/SimpleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ASimpleGun::OnAttack()
{
    if (GetWorld() == nullptr || WeaponOwner == nullptr || BPProjectile == nullptr)
        return;

    // 射出をプレイヤー正面方向に設定
    FVector MuzzleLocation = WeaponOwner->GetActorLocation() + WeaponOwner->GetActorForwardVector() * 100.f + WeaponOwner->MazzleOffset;

    // 生成に必要な情報を設定
    // 発射口をプレイヤーの中心あたりに設定
    FVector PlayerCenterLocation = WeaponOwner->GetActorLocation() + WeaponOwner->MazzleOffset;
    // 初速度を射出方向にする
    FVector LaunchDir = (MuzzleLocation - PlayerCenterLocation).GetSafeNormal();
    // 射出方向への回転
    FRotator MuzzleRotation = LaunchDir.Rotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = WeaponOwner;
    SpawnParams.Instigator = WeaponOwner->GetInstigator();
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // 弾の生成
    ASimpleProjectile* Projectile = GetWorld()->SpawnActor<ASimpleProjectile>(
        BPProjectile,
        MuzzleLocation,
        MuzzleRotation,
        SpawnParams
    );

    if (Projectile)
    {
        // 初速の設定
        Projectile->ProjectileMovement->Velocity = LaunchDir * Projectile->ProjectileMovement->InitialSpeed;
        // ダメージの設定
        Projectile->Damage = Damage;
    }
}
