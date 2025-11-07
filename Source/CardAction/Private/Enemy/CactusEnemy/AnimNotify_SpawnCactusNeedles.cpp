// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CactusEnemy/AnimNotify_SpawnCactusNeedles.h"
#include <Enemy/CactusEnemy/CactusEnemy.h>
#include <Enemy/CactusEnemy/CactusNeedle.h>
#include "Grid/GridManager.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>

void UAnimNotify_SpawnCactusNeedles::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp == nullptr)
        return;

    AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGameMode == nullptr)
        return;

    AGridManager* GridManager = MyGameMode->GridManager;
    if (GridManager == nullptr)
        return;

    AActor* Owner = MeshComp->GetOwner();
    ACactusEnemy* Enemy = Cast<ACactusEnemy>(Owner);
    if (Enemy == nullptr || Enemy->AttackClass == nullptr)
        return;

    // スポーンパラメータ設定
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // 前後左右のセルにカクタスニードルを生成
    FCoord CurrentCoord = Enemy->GetCurrentCoord();
    FCoord SpawnCoord = FCoord::Zero();
    for (int i = 0;i < 4; i++)
    {
        switch (i)
        {
        case 0: SpawnCoord = CurrentCoord + FVector2D(1.f, 0.f); break;
        case 1: SpawnCoord = CurrentCoord + FVector2D(-1.f, 0.f); break;
        case 2: SpawnCoord = CurrentCoord + FVector2D(0.f, 1.f); break;
        case 3: SpawnCoord = CurrentCoord + FVector2D(0.f, -1.f); break;
        }

        // プレイヤーが乗っていない かつ アクセスできない場合、生成しない
        if (GridManager->IsExistPlayerOnGridCell(SpawnCoord) == false && GridManager->IsAccessableGridCell(SpawnCoord) == false)
            continue;

        // 生成する位置を取得
        FVector SpawnLocation = GridManager->ConvertToWorldPosition(SpawnCoord);

        // 生成
        ACactusNeedle* CactusNeedle = GetWorld()->SpawnActor<ACactusNeedle>(Enemy->AttackClass, SpawnLocation, FRotator(0.f, 0.f, 0.f), Params);
        if (CactusNeedle == nullptr)
            return;

        // 初期設定
        CactusNeedle->Setup();
    }
}