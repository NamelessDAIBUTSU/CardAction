// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "CardDetailPanelWidget.generated.h"

/// <summary>
/// ウィジェット：カード詳細パネルウィジェット
/// </summary>
UCLASS()
class CARDACTION_API UCardDetailPanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	// カード情報を詳細パネルに設定
	void Setup(class UCardData* Data);

public:
	// 名前テキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardNameText = nullptr;

	// レアリティテキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RarityText = nullptr;

	// 属性テキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ElementText = nullptr;

	// ダメージテキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText = nullptr;

	// 効果テキスト
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardDescText = nullptr;
};
