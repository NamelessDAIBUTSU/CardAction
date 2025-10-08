// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/EnemyHPBar.h"
#include <Components/WidgetComponent.h>

void UEnemyHPBar::NativeConstruct()
{
	Super::NativeConstruct();

	// �X�V�Ɏg���I�u�W�F�N�g���擾���Ă���
	{
		if (HPBar == nullptr)
		{
			HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EnemyHPBar")));
		}
	}
}

void UEnemyHPBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// HP�o�[�̍X�V
	OnUpdateHPBar();
}

void UEnemyHPBar::OnUpdateHPBar()
{
	if (HPBar && Owner)
	{
		// 0���Z���
		if (Owner->MaxHP == 0)
			return;

		// �Q�[�W�X�V
		float Rate = Owner->CurrentHP / (float)Owner->MaxHP;
		HPBar->SetPercent(Rate);
	}
}
