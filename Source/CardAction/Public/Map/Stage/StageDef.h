#pragma once

#include "CoreMinimal.h"
#include "StageDef.generated.h"

// ステージの進行方向に繋がるステージの最小・最大数
#define MIN_STAGE_CHAIN_NUM 1
#define MAX_STAGE_CHAIN_NUM 3

// ステージウィジェットの1辺のサイズ
#define STAGE_WIDGET_SIZE 64
// ステージウィジェットの水平方向のマージンサイズ
#define STAGE_WIDGET_VERTICAL_MERGIN 32


// ステージの種類
UENUM(BlueprintType)
enum class EStageType : uint8
{
    Enemy    UMETA(DisplayName = "Enemy"),
    Boss     UMETA(DisplayName = "Boss"), 
    Bonus    UMETA(DisplayName = "Bonus"),
};

// ステージ状況
UENUM(BlueprintType)
enum class EStageCondition : uint8
{
    NotSelect   UMETA(DisplayName = "NotSelect"),
    CanSelect   UMETA(DisplayName = "CanSelect"),
    Clear       UMETA(DisplayName = "Clear"),
};