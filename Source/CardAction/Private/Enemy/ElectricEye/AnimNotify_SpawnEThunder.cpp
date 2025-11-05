// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ElectricEye/AnimNotify_SpawnEThunder.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include <Enemy/ElectricEye/ElectricEyeEnemy.h>
#include <AIController.h>
#include <Enemy/ElectricEye/ElectricThunder.h>
#include "Grid/GridManager.h"


void UAnimNotify_SpawnEThunder::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp == nullptr)
        return;

    AActor* Owner = MeshComp->GetOwner();
    AElectricEyeEnemy* Enemy = Cast<AElectricEyeEnemy>(Owner);
    if (Enemy == nullptr || Enemy->AttackClass == nullptr)
        return;

    AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGameMode == nullptr)
        return;

    AGridManager* GridManager = MyGameMode->GridManager;
    if (GridManager == nullptr)
        return;


    // スポーンパラメータ設定
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // エレクトリックサンダースポーン
    FVector2D GridSize = GridManager->GetGridSize();
    int Count = 0;
    for (int i = 0; i < SpawnEThunderNum; i++)
    {
        // エレクトリックサンダーを降らせる座標を取得する
        FVector2D SpawnCoord = FVector2D::Zero();
        do {
            // ループ防止用
            Count++;

            float RandomX = FMath::RandRange(0, (int)GridSize.X - 1);
            float RandomY = FMath::RandRange(0, (int)GridSize.Y - 1);
            SpawnCoord = FVector2D(RandomX, RandomY);
        } while (GridManager->IsAccessableGridCell(SpawnCoord) == false && Count < 10);
        FVector SpawnLocation = GridManager->ConvertToWorldPosition(SpawnCoord);

        // スポーン
        AElectricThunder* ElectricThunder = GetWorld()->SpawnActor<AElectricThunder>(Enemy->AttackClass, SpawnLocation, FRotator(0.f, 0.f, 0.f), Params);
        if (ElectricThunder == nullptr)
            return;

        // 攻撃予測の追加
        GridManager->AddAttackSign(SpawnCoord);
    }
}