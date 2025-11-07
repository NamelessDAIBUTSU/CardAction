// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_GridMove.h"
#include "AIController.h"
#include <Enemy/EnemyBase.h>
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Grid/GridManager.h"

UBTTask_GridMove::UBTTask_GridMove()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_GridMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return EBTNodeResult::Failed;

	AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());
	if (Enemy == nullptr)
		return EBTNodeResult::Failed;

	UGridMovementComponent* GridMoveComp = Enemy->GetGridMovementComponent();
	if (GridMoveComp == nullptr)
		return EBTNodeResult::Failed;

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode == nullptr)
		return EBTNodeResult::Failed;

	AGridManager* GridManager = MyGameMode->GridManager;
	if (GridManager == nullptr)
		return EBTNodeResult::Failed;


	// 移動先をランダムに取得
	int Min = 0;
	int Max = 3;
	// 斜め移動もOKなら抽選対象に含める
	if (bCanMoveDiagonal)
	{
		Max = 7;
	}

	// 移動先セルの抽選
	FCoord Dir = FCoord::Zero();
	int Count = 0;
	do {
		// 経路を見つけられなかったので失敗
		if(Count > 10)
			return EBTNodeResult::Failed;

		// 抽選
		int RandomDir = FMath::RandRange(Min, Max);
		switch (RandomDir)
		{
		case 0:
			Dir = FCoord(0, 1); break;
		case 1:
			Dir = FCoord(0, -1); break;
		case 2:
			Dir = FCoord(1, 0); break;
		case 3:
			Dir = FCoord(-1, 0); break;
		case 4:
			Dir = FCoord(1, 1); break;
		case 5:
			Dir = FCoord(-1, 1); break;
		case 6:
			Dir = FCoord(1, -1); break;
		case 7:
			Dir = FCoord(-1, -1); break;
		}
		TargetCoord = GridMoveComp->GetCurrentCoord() + Dir;

		// ループ回避用のカウント
		Count++;

	} while (GridManager->IsAccessableGridCell(TargetCoord) == false);

	// グリッド移動命令
	GridMoveComp->RequestMoveToDirection(TargetCoord, GoalSec);

	return EBTNodeResult::InProgress;
}

void UBTTask_GridMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return;

	AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());
	if (Enemy == nullptr)
		return;

	UGridMovementComponent* GridMoveComp = Enemy->GetGridMovementComponent();
	if (GridMoveComp == nullptr)
		return;

	// ターゲットの座標にたどり着いたらタスク終了
	if (GridMoveComp->IsMoving() == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
