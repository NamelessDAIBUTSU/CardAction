#pragma once

#include "CoreMinimal.h"
#include "BattlePhaseDef.generated.h"

UENUM(BlueprintType)
enum class EBattlePhase : uint8
{
    None        UMETA(DisplayName = "None"),
    Entry       UMETA(DisplayName = "Entry"),       // エントリーフェーズ
    Action      UMETA(DisplayName = "Action"),      // アクションフェーズ
    CardSelect  UMETA(DisplayName = "CardSelect"),  // カード選択フェーズ
    Result      UMETA(DisplayName = "Result"),      // リザルトフェーズ
};