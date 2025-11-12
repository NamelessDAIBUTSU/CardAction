// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "FadeWidget.generated.h"

// フェードの種類
UENUM(BlueprintType)
enum class EFadeType : uint8
{
	None    UMETA(DisplayName = "None"),
	FadeIn  UMETA(DisplayName = "FadeIn"),
	FadeOut UMETA(DisplayName = "FadeOut"),
};

UCLASS()
class CARDACTION_API UFadeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	// フェード処理
	void FadeIn(float InFadeSec = 1.f);
	void FadeOut(float OutFadeSec = 1.f);

	// フェード更新
	void UpdateFade(float DeltaSec);

	// フェード中か
	bool IsFade();
	bool IsFadeIn();
	bool IsFadeOut();

	// フェード終了時のコールバック登録
	void SetOnFadeOutFinished(TFunction<void()> Func);


private:
	// フェードするウィジェット
	UPROPERTY(meta = (BindWidget))
	UImage* FadeMask;

	// フェード更新時間用
	float ElapsedSec = 0.f;

	// 毎フレームのフェード変化量
	float FadeSpeed = 0.f;

	// 現在のフェードタイプ
	EFadeType CurrentFadeType = EFadeType::None;

	// フェードアウト終了時のコールバック
	TFunction<void()> OnFadeOutFinished;
};
