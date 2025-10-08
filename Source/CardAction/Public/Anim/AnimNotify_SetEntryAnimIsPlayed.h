// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetEntryAnimIsPlayed.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UAnimNotify_SetEntryAnimIsPlayed : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
