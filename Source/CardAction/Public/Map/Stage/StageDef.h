#pragma once

#include "CoreMinimal.h"
#include "StageDef.generated.h"

// �X�e�[�W�̐i�s�����Ɍq����X�e�[�W�̍ŏ��E�ő吔
#define MIN_STAGE_CHAIN_NUM 1
#define MAX_STAGE_CHAIN_NUM 3

// �X�e�[�W�̎��
UENUM(BlueprintType)
enum class EStageType : uint8
{
    Enemy    UMETA(DisplayName = "Enemy"),
    Boss     UMETA(DisplayName = "Boss"), 
    Bonus    UMETA(DisplayName = "Bonus"),
};
