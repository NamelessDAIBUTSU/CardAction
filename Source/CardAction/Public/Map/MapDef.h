#pragma once

#include "CoreMinimal.h"
#include "MapDef.generated.h"

// ゲームクリアに必要なマップ数
#define NEED_CLEAR_MAP_NUM 4

// マップの種類
UENUM(BlueprintType)
enum class EMapType : uint8
{
    Normal      UMETA(DisplayName = "Normal"),
    Lava        UMETA(DisplayName = "Lava"),
    Ice         UMETA(DisplayName = "Ice"),
    Woods         UMETA(DisplayName = "Woods"),
    Water         UMETA(DisplayName = "Water"),
};
