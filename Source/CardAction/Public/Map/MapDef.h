#pragma once

#include "CoreMinimal.h"
#include "MapDef.generated.h"

// �Q�[���N���A�ɕK�v�ȃ}�b�v��
#define NEED_CLEAR_MAP_NUM 4

// �}�b�v�̎��
UENUM(BlueprintType)
enum class EMapType : uint8
{
    Normal      UMETA(DisplayName = "Normal"),
    Lava        UMETA(DisplayName = "Lava"),
    Ice         UMETA(DisplayName = "Ice"),
    Woods         UMETA(DisplayName = "Woods"),
    Water         UMETA(DisplayName = "Water"),
};
