// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardData.h"
#include "InitDeckData.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UInitDeckData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// �f�b�L��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FName Name;

	// �f�b�L����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Description;

	// �����J�[�h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<UCardData*> Cards;
};
