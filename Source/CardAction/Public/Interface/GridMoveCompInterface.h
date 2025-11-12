// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <MyComponents/GridMovementComponent.h>
#include "GridMoveCompInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGridMoveCompInterface : public UInterface
{
	GENERATED_BODY()
};

class CARDACTION_API IGridMoveCompInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UGridMovementComponent* GetGridMoveComponent() = 0;
};