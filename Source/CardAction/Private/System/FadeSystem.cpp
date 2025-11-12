// Fill out your copyright notice in the Description page of Project Settings.


#include "System/FadeSystem.h"
#include <Kismet/GameplayStatics.h>

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

void UFadeSystem::FadeOutAndOpenLevel(FName LevelName, float FadeSec)
{
	if (FadeWidget == nullptr)
		return;

	// フェードアウト
	FadeWidget->FadeOut(FadeSec);

	// 遷移先のレベルの読み込みをフェード後にするよう設定
	FadeWidget->SetOnFadeOutFinished(
		[this, LevelName]() {
			UGameplayStatics::OpenLevel(GetWorld(), LevelName);

			FadeIn();
		});

	// マップロード完了イベント登録
	WorldDelegate.PostLoadMapWithWorld.AddUObject(this, &UFadeSystem::OnPostLoadLevel);
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

// レベル読み込み後のコールバック
void UFadeSystem::OnPostLoadLevel(UWorld* LoadedWorld)
{
	// Viewport再登録
	if (FadeWidget)
	{
		FadeWidget->AddToViewport(100);
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(LoadedWorld, 0);
	if (PC && FadeWidget)
	{
		PC->bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(FadeWidget->TakeWidget());
		PC->SetInputMode(InputMode);
	}
}
