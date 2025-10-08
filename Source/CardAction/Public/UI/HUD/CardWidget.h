// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Card/CardData.h>
#include "Card/SelectCardDelegate.h"

#include "CardWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected: /* UUserWidget */
	virtual void NativeConstruct() override;


public:
	// 初期化
	void Initialize(UCardData* Data, FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate);
	// ウィジェットのみ初期化
	void InitializeWidget(UCardData* Data);

	// カードデータの取得
	UCardData* GetCardData() const { return CardData; }

	// マウスイベント
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// 効果発動
	void ExecuteEffect();

private:
	// カードデータ
	UPROPERTY(VisibleAnywhere, Category = "Data")
	UCardData* CardData = nullptr;

	// 選択中カードに追加するデリゲート
	FOnSelectCard SelectCardDelegate;
	// 選択中カードから除去するデリゲート
	FOnUnSelectCard UnSelectCardDelegate;

	// 選択中か
	bool bSelected = false;
};
