#pragma once


#include "CoreMinimal.h"
#include "GridCellDef.generated.h"

// グリッドセルサイズ
#define GRID_CELL_UNIT 200 

// グリッドセルの種類
UENUM(BlueprintType)
enum class EGridCellType : uint8
{
    None    UMETA(DisplayName = "None"),
    Normal  UMETA(DisplayName = "Normal"),
};

