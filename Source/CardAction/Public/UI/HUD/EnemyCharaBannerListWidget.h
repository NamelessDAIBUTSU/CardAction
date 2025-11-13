// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include "UI/HUD/CharaBannerWidget.h"
#include <Components/VerticalBox.h>
#include "EnemyCharaBannerListWidget.generated.h"

/// <summary>
/// ウィジェット：敵のバナーをリスト管理するウィジェット
/// </summary>
UCLASS()
class CARDACTION_API UEnemyCharaBannerListWidget : public UHUDBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// バナーの初期化
	void InitializeBanner();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CharaBannerWidgetClass;

	UPROPERTY()
	TArray<UCharaBannerWidget*> CharaBannerWidgets;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBannerBox;
};
