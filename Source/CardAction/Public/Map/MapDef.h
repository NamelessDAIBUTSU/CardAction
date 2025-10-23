#pragma once

#include "CoreMinimal.h"
#include "MapDef.generated.h"

// ƒ}ƒbƒv‚ÌŽí—Þ
UENUM(BlueprintType)
enum class EMapType : uint8
{
    Normal      UMETA(DisplayName = "Normal"),
    Lava      UMETA(DisplayName = "Lava"),
    Ice    UMETA(DisplayName = "Ice"),
};
