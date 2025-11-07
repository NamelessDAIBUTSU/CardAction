// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoordDef.generated.h"

USTRUCT(BlueprintType)
struct CARDACTION_API FCoord
{
	GENERATED_BODY()

public:
	FCoord() {}
	FCoord(int32 Pos) { X = Pos; Y = Pos; }
	FCoord(int32 PosX, int32 PosY) { X = PosX; Y = PosY; }
	FCoord(const FCoord& Coord) { X = Coord.X; Y = Coord.Y; }

public:
	static FCoord Zero() { return FCoord(0); }
	FVector2D Vector2D() { return FVector2D(X, Y); }

public: /* operator */
	bool operator==(const FCoord& Coord);
	bool operator!=(const FCoord& Coord);
	FCoord operator+(const FCoord& Coord);
	FCoord operator+(const FVector2D& Dir);
	FCoord operator-(const FCoord& Coord);
	FCoord operator-(const FVector2D& Dir);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y = 0;
};
