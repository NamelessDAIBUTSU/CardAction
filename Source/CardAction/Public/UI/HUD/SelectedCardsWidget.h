// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/HorizontalBox.h>
#include <UI/HUD/CardWidget.h>
#include "Components/PanelSlot.h"
#include <Components/SizeBox.h>
#include "SelectedCardsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API USelectedCardsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 選択中カードに追加
	UFUNCTION()
	void AddToSelectedCards(UCardData* Data);

	UFUNCTION()
	void RemoveFromSelectedCards(UCardData* Data);

	// 発動
	void OnExecute();

public:
	// 手札の最大数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	int MaxSelectedCardsNum = 3;

	// カードクラス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> CardsWidgetClass;

	// 選択中カードボックス
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* CardsHorizontalBox;

	// 左右端マージン
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Margin")
	FMargin EdgeMargin;
	// カード間マージン
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Margin")
	float Margin = 6.f;
};
