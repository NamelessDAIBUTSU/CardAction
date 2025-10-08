#pragma once

#include "CoreMinimal.h"
#include "CardTypeDef.generated.h"

UENUM(BlueprintType)
enum class ECardType : uint8
{
    SummonWeapon    UMETA(DisplayName = "SummonWeapon"),
    Magic           UMETA(DisplayName = "Magic"),
    Buff            UMETA(DisplayName = "Buff"),
    Debuff          UMETA(DisplayName = "Debuff")
};