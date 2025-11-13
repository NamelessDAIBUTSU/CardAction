#pragma once


#include "CoreMinimal.h"
#include "GridCellDef.generated.h"

// グリッドセルサイズ
#define GRID_CELL_UNIT 200 
#define GRID_CELL_HEIGHT_UNIT 150 

/// <summary>
/// グリッドセルの種類
/// </summary>
UENUM(BlueprintType)
enum class EGridCellType : uint8
{
    None    UMETA(DisplayName = "None"),
    Normal  UMETA(DisplayName = "Normal"),
};

