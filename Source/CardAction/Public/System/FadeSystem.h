// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <UI/FadeWidget.h>
#include "FadeSystem.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UFadeSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void FadeOutAndOpenLevel(FName LevelName, float FadeSec = 1.f);
	void FadeIn(float FadeSec = 1.f);
	void FadeOut(float FadeSec = 1.f);

	// フェード中か
	bool IsFade();
	bool IsFadeIn();
	bool IsFadeOut();

	// フェード更新
	void UpdateFade(float DeltaSec);

	// レベル読み込み後のコールバック
	UFUNCTION()
	void OnPostLoadLevel(UWorld* LoadedWorld);

private:
	UPROPERTY();
	UFadeWidget* FadeWidget;

	// 毎フレーム更新用のデリゲートハンドル
	FDelegateHandle TickHandle;

	// レベル切り替え時用のデリゲート
	FCoreUObjectDelegates WorldDelegate;
};
