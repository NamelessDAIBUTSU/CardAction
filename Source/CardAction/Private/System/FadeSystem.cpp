// Fill out your copyright notice in the Description page of Project Settings.


#include "System/FadeSystem.h"

void UFadeSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Widgetの生成
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			static TSubclassOf<UUserWidget> FadeWidgetClass =
				StaticLoadClass(UUserWidget::StaticClass(), nullptr,
					TEXT("/Game/CardAction/UI/WBP_Fade.WBP_Fade_C"));
			if (FadeWidgetClass)
			{
				UWorld* World = GetWorld();
				if (World == nullptr)
				{
					World = GEngine->GetWorldFromContextObjectChecked(GetOuter());
				}

				FadeWidget = CreateWidget<UFadeWidget>(World, FadeWidgetClass);
				if (FadeWidget)
				{
					// 最前面に配置
					FadeWidget->AddToViewport(1000);
					FadeWidget->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}, 0.1f, false);


	// Ticker登録
	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime)
			{
				UpdateFade(DeltaTime);
				return true; // trueを返すと継続実行
			})
	);
}

void UFadeSystem::FadeIn(float FadeSec)
{
	if (FadeWidget)
	{
		FadeWidget->FadeIn(FadeSec);
	}
}

void UFadeSystem::FadeOut(float FadeSec)
{
	if (FadeWidget)
	{
		FadeWidget->FadeOut(FadeSec);
	}
}

bool UFadeSystem::IsFade()
{
	if (FadeWidget == nullptr)
		return false;
	
	return IsFadeIn() || IsFadeOut();
}

bool UFadeSystem::IsFadeIn()
{
	if (FadeWidget == nullptr)
		return false;

	return FadeWidget->IsFadeIn();
}

bool UFadeSystem::IsFadeOut()
{
	if (FadeWidget == nullptr)
		return false;

	return FadeWidget->IsFadeOut();
}

// フェード更新
void UFadeSystem::UpdateFade(float DeltaSec)
{
	if (IsFade() == false)
		return;

	if (FadeWidget)
	{
		FadeWidget->UpdateFade(DeltaSec);
	}
}