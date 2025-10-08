#pragma once


#include "CoreMinimal.h"
#include "GridCellDef.generated.h"

// �O���b�h�Z���T�C�Y
#define GRID_CELL_UNIT 200 

// �O���b�h�Z���̎��
UENUM(BlueprintType)
enum class EGridCellType : uint8
{
    None    UMETA(DisplayName = "None"),
    Normal  UMETA(DisplayName = "Normal"),
};

