// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapObject.h"
#include "Map/Stage/StageObject.h"

void UMapObject::Initialize(UMapData* Data)
{
    if (Data == nullptr)
        return;

    MapData = Data;

    // マップサイズをランダムに決める
    int Width = FMath::RandRange(Data->MinWidth, Data->MaxWidth);
    Size = FVector2D(Width, Data->Height);
}

// 指定位置のステージを取得
UStageObject* UMapObject::GetStage(FVector2D Pos)
{
    for (UStageObject* Stage : StageList)
    {
        if (Stage == nullptr)
            continue;

        if (Stage->GetPos() == Pos)
        {
            return Stage;
        }
    }

    return nullptr;
}

void UMapObject::AddStageList(class UStageObject* Stage)
{
    StageList.Add(Stage);
}
