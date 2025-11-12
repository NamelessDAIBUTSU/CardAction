// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PumpkinEnemy/PumpkinEnemy.h"


void APumpkinEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// 回転可能か
bool APumpkinEnemy::CanRotate()
{
	// 攻撃モンタージュ再生中は回転を制御
	if (GetMesh())
	{
		if (GetMesh()->GetAnimInstance())
		{
			return GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false;
		}
	}

	return true;
}
