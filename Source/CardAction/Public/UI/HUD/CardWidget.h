// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Card/CardData.h>
#include "Card/SelectCardDelegate.h"

#include "CardWidget.generated.h"

// 表示箇所によって処理が違うのでオプション構造体
USTRUCT()
struct CARDACTION_API FCardWidgetOption
{
	GENERATED_BODY()

public:
	// 選択時の処理デリゲート
	FOnSelectCard SelectCardDelegate;
	// 選択解除時の処理デリゲート
	FOnUnSelectCard UnSelectCardDelegate;

	// マウスオーバー可能か
	bool bCanMouseOver = true;
	// マウスオーバーで拡大するか
	bool bChangeScale = true;
	// マウスオーバーでツールチップを表示するか
	bool bShowToolTip = false;
};

UCLASS()
class CARDACTION_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected: /* UUserWidget */
	virtual void NativeConstruct() override;


public:
	// 初期化
	void Initialize(UCardData* Data, const FCardWidgetOption& WidgetOption);

	// カードデータの設定
	void SetupCardData(UCardData* Data);

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

	FCardWidgetOption Option;

	// 選択中か
	bool bSelected = false;
};
