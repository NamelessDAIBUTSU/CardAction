// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UI/HUD/CardWidget.h>
#include <Components/HorizontalBox.h>
#include "Card/SelectCardDelegate.h"

#include "HandCardsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UHandCardsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// カード選択デリゲートを設定
	void SetSelectCardDelegate(FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate);

	// 手札にカードを追加
	void AddToHandCards(UCardData* CardData);

public:
	// 手札の最大数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HandCards")
	int MaxHandCardsNum = 5;

	// カードクラス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> CardsWidgetClass;

	// 手札のボックス
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* CardsHorizontalBox;

private:
	// 手札
	UPROPERTY()
	TArray<UCardWidget*> HandCards;

	// 選択中カードに追加するデリゲート
	FOnSelectCard SelectCardDelegate;
	// 選択状態を解除するデリゲート
	FOnUnSelectCard UnSelectCardDelegate;
};
