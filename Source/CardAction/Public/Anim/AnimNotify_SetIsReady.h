// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetIsReady.generated.h"

/// <summary>
/// アニメーション通知：ゲーム開始フラグを立てる
/// </summary>
UCLASS()
class CARDACTION_API UAnimNotify_SetIsReady : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
