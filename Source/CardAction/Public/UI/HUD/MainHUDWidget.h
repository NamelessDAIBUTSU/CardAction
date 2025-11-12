// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "UI/HUD/HandCardsWidget.h"
#include "UI/HUD/StageClearWidget.h"
#include "CardSelectWidget.h"
#include "Card/SelectCardDelegate.h"
#include "EnemyCharaBannerListWidget.h"
#include "Components/SizeBox.h"
#include "ActionTimeWidget.h"
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
    void OnUpdate(float DeltaSec);

    // アクションフェーズ以外で非表示にするUIの表示制御
    void SetVisibleExceptActionPhase(bool Visible);

    // 各Widgetの初期化
    void InitializeWidgets();

private:
    // 各Widgetの生成 & 配置
    void CreateWidgets();


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

    // 手札
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HandCardsWidgetClass;

    // カード選択
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> CardSelectWidgetClass;

    // エネミーキャラバナー
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> EnemyCharaBannerWidgetClass;

    // 制限時間
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ActionTimeWidgetClass;

public: /* インスタンスのポインタ */
    // インスタンス化させたHUDのリスト
    TArray<UHUDBase*> HUDList;

    // ステージクリア
    UPROPERTY()
    UStageClearWidget* StageClearWidget = nullptr;
    // ゲームオーバー
    UPROPERTY()
    UUserWidget* GameOverWidget = nullptr;
    // 手札
    UPROPERTY()
    UHandCardsWidget* HandCardsWidget = nullptr;
    // カード選択
    UPROPERTY()
    UCardSelectWidget* CardSelectWidget = nullptr;
    // エネミーキャラバナー
    UPROPERTY(meta = (BindWidget))
    USizeBox* EnemyCharaBannerBox;
    UPROPERTY()
    UEnemyCharaBannerListWidget* EnemyCharaBannerWidget = nullptr;
    // 制限時間
    UPROPERTY()
    UActionTimeWidget* ActionTimeWidget;

public: /* Delegate */
    // カード選択用デリゲート
    FOnSelectCard SelectCardDelegate;
    // カード選択解除用デリゲート
    FOnUnSelectCard UnSelectCardDelegate;
};
