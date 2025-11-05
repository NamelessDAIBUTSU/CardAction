// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnEThunder.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UAnimNotify_SpawnEThunder : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

private:
	int SpawnEThunderNum = 2;
};
