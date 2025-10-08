// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PumpkinEnemy/PumpkinEnemy.h"


void APumpkinEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// ‰ñ“]‰Â”\‚©
bool APumpkinEnemy::CanRotate()
{
	// UŒ‚ƒ‚ƒ“ƒ^[ƒWƒ…Ä¶’†‚Í‰ñ“]‚ð§Œä
	if (GetMesh())
	{
		if (GetMesh()->GetAnimInstance())
		{
			return GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false;
		}
	}

	return true;
}
