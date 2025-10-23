// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Stage/StageObject.h"

void UStageObject::AddChainedStage(UStageObject* ChainedStage)
{
	ChainedStageList.Add(ChainedStage);
}

void UStageObject::AddPreStage(UStageObject* PreStage)
{
	PreStageList.Add(PreStage);
}

