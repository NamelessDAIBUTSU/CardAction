// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <UI/HUD/CardWidget.h>
#include <UI/HUD/CardSlotWidget.h>
#include <Components/HorizontalBox.h>
#include "Card/SelectCardDelegate.h"

#include "HandCardsWidget.generated.h"

/// <summary>
/// ウィジェット：手札ウィジェット
/// </summary>
UCLASS()
class CARDACTION_API UHandCardsWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// 初期化
	virtual void NativeConstruct() override;

public: /* UHUDBase */
	// アクションフェーズ以外で非表示
	virtual bool IsVisibleExceptActionPhase() override{ return false; }

public:
	// カード選択デリゲートを設定
	void SetSelectCardDelegate(FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate);

	// 手札にカードを追加
	void AddToHandCards(int Index, UCardData* CardData);

	// 手札カードをリセット
	void ResetHandCards();
	void ResetHandCards(int Index);

	// カード選択
	void SelectCard(int SelectIndex);

	// カードの効果発動
	void ExecuteEffect(int Index);

	// カードウィジェットのアニメーションをデフォルトに戻す
	void PlayDefaultAnimation(int Index);

public:
	// カードスロットクラス
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CardSlotWidgetClass;

	// 手札のボックス
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* CardsHorizontalBox;

private:
	// 手札
	UPROPERTY(VisibleAnywhere)
	TArray<UCardSlotWidget*> HandCards;

	// 選択中カードに追加するデリゲート
	FOnSelectCard SelectCardDelegate;
	// 選択状態を解除するデリゲート
	FOnUnSelectCard UnSelectCardDelegate;
};
