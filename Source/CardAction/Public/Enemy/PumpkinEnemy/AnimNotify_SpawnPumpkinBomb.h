// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnPumpkinBomb.generated.h"

/// <summary>
/// アニメーション通知：パンプキンボム生成
/// </summary>
UCLASS()
class CARDACTION_API UAnimNotify_SpawnPumpkinBomb : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
