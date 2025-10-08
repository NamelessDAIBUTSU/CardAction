// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/EnemyHPBar.h"
#include <Components/WidgetComponent.h>

void UEnemyHPBar::NativeConstruct()
{
	Super::NativeConstruct();

	// 更新に使うオブジェクトを取得しておく
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

	// HPバーの更新
	OnUpdateHPBar();
}

void UEnemyHPBar::OnUpdateHPBar()
{
	if (HPBar && Owner)
	{
		// 0除算回避
		if (Owner->MaxHP == 0)
			return;

		// ゲージ更新
		float Rate = Owner->CurrentHP / (float)Owner->MaxHP;
		HPBar->SetPercent(Rate);
	}
}
