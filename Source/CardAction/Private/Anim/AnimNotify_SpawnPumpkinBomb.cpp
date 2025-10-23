// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/AnimNotify_SpawnPumpkinBomb.h"
#include <Enemy/PumpkinEnemy/PumpkinEnemy.h>
#include <Enemy/PumpkinEnemy/PumpkinBomb.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Particles/ParticleSystemComponent.h"
#include "Grid/Cell/GridCellActor.h"
#include "Grid/GridManager.h"

void UAnimNotify_SpawnPumpkinBomb::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp == nullptr)
        return;

    AActor* Owner = MeshComp->GetOwner();
    APumpkinEnemy* Enemy = Cast<APumpkinEnemy>(Owner);
    if (Enemy == nullptr || Enemy->AttackClass == nullptr)
        return;

    // �X�|�[���p�����[�^�ݒ�
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // ���ڂ��ᔚ�e�X�|�[��
    APumpkinBomb* PumpkinBomb = GetWorld()->SpawnActor<APumpkinBomb>(Enemy->AttackClass, Enemy->GetActorLocation(), FRotator(0.f, 0.f, 0.f), Params);
    if (PumpkinBomb == nullptr)
        return;

    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (APawn* Pawn = PlayerController->GetPawn())
        {
            AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
            if (AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode))
            {
                AGridManager* GridManager = MyGameMode->GridManager;
                if (GridManager == nullptr)
                    return;

                // �ڕW�n�_�̃O���b�h�Z���̎擾
                AGridCellActor* TargetCell = GridManager->GetGridCellActor(Pawn->GetActorLocation());
                if (TargetCell == nullptr)
                    return;

                // �ړ��ɕK�v�ȏ��̏����ݒ�
                PumpkinBomb->Setup(TargetCell->GetActorLocation());

                // �U���\���̒ǉ�
                GridManager->AddAttackSign(TargetCell->CellData.GridCoord);
            }
        }
    }
}