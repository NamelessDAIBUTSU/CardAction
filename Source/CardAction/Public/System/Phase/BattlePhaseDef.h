#pragma once

#include "CoreMinimal.h"
#include "BattlePhaseDef.generated.h"

UENUM(BlueprintType)
enum class EBattlePhase : uint8
{
    Action      UMETA(DisplayName = "Action"),      // �A�N�V�����t�F�[�Y
    CardSelect  UMETA(DisplayName = "CardSelect"),  // �J�[�h�I���t�F�[�Y
    Result      UMETA(DisplayName = "Result"),      // ���U���g�t�F�[�Y
};