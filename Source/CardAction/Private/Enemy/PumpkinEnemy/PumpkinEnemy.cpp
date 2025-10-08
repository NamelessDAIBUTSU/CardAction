// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PumpkinEnemy/PumpkinEnemy.h"


void APumpkinEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// ��]�\��
bool APumpkinEnemy::CanRotate()
{
	// �U�������^�[�W���Đ����͉�]�𐧌�
	if (GetMesh())
	{
		if (GetMesh()->GetAnimInstance())
		{
			return GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false;
		}
	}

	return true;
}
