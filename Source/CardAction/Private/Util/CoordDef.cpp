// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/CoordDef.h"

bool FCoord::operator==(const FCoord& Coord)
{
	return X == Coord.X && Y == Coord.Y;
}

bool FCoord::operator!=(const FCoord& Coord)
{
	return !((*this) == Coord);
}

FCoord FCoord::operator+(const FCoord& Coord)
{
	FCoord ReturnCoord = FCoord(X + Coord.X, Y + Coord.Y);
	return ReturnCoord;
}

FCoord FCoord::operator+(const FVector2D& Dir)
{
	FCoord ReturnCoord = FCoord(X + Dir.X, Y + Dir.Y);
	return ReturnCoord;
}

FCoord FCoord::operator-(const FCoord& Coord)
{
	FCoord ReturnCoord = FCoord(X - Coord.X, Y - Coord.Y);
	return ReturnCoord;
}

FCoord FCoord::operator-(const FVector2D& Dir)
{
	FCoord ReturnCoord = FCoord(X - Dir.X, Y - Dir.Y);
	return ReturnCoord;
}
