// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "UI/HUD/SelectedCardsWidget.h"
#include "UI/HUD/HPGauge.h"
#include "UI/HUD/HandCardsWidget.h"
#include "UI/HUD/StageClearWidget.h"
#include "CardSelectWidget.h"
#include "Card/SelectCardDelegate.h"

#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected: /* UUserWidget */
    // 初期化
    virtual void NativeConstruct() override;

public:
    void OnTick(float DeltaTime);


private: /* Callback */
    // 選択中カードに追加
    void OnAddToSelectedCards(UCardData* CardData);
    // 選択中カードを除去
    void OnRemoveFromSelectedCards(UCardData* CardData);
	

public: /* 生成するWidgetクラス */
    // CanvasPanelをバインド
    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* MainCanvas;

    // ステージクリア
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> StageClearWidgetClass;

    // ゲームオーバー
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    // HPゲージ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HPGaugeWidgetClass;

    // 手札
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HandCardsWidgetClass;

    // 選択中カード
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> SelectedCardsWidgetClass;

    // カード選択
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> CardSelectWidgetClass;


public: /* インスタンスのポインタ */
    // ステージクリア
    UPROPERTY()
    UStageClearWidget* StageClearWidget = nullptr;
    // ゲームオーバー
    UPROPERTY()
    UUserWidget* GameOverWidget = nullptr;
    // HPゲージ
    UPROPERTY()
    UHPGauge* HPGaugeWidget = nullptr;
    // 手札
    UPROPERTY()
    UHandCardsWidget* HandCardsWidget = nullptr;
    // 選択中カード
    UPROPERTY()
    USelectedCardsWidget* SelectedCardsWidget = nullptr;
    // カード選択
    UPROPERTY()
    UCardSelectWidget* CardSelectWidget = nullptr;


public: /* Delegate */
    // カード選択時のデリゲート
    FOnSelectCard SelectCardDelegate;
    // 選択状態を解除するデリゲート
    FOnUnSelectCard UnSelectCardDelegate;
};
