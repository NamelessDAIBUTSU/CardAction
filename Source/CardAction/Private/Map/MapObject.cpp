// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/MapObject.h"
#include "Map/Stage/StageObject.h"

// �w��ʒu�̃X�e�[�W���擾
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
