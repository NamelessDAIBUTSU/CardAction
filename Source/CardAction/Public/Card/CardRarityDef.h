#pragma once

#include "CoreMinimal.h"
#include "CardRarityDef.generated.h"

UENUM(BlueprintType)
enum class ECardRarity : uint8
{
    Common     UMETA(DisplayName = "Common"),
    Rare       UMETA(DisplayName = "Rare"),
    Epic       UMETA(DisplayName = "Epic"),
    Legendary  UMETA(DisplayName = "Legendary")
};