// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "Components/SizeBox.h"
#include "CardSelectWidget.generated.h"


UCLASS()
class CARDACTION_API UCardSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 初期化
	virtual bool Initialize() override;

public:
	// 決定時のコールバック
	UFUNCTION()
	void OnDecide();

	// ビジブル変更時のコールバック
	UFUNCTION()
	void OnChangeVisibility(ESlateVisibility NextVisibility);
	UFUNCTION()
	void OnChangeIsDecided();

	// アクションフェーズへの遷移判定
	bool GetIsDecided() const { return bIsDecided; }

	// Inアニメーションの再生
	void PlayInAnimation();

	// カードウィジェットの生成
	void CreateCardWidgets(const TArray<class UCardData*>& CardDataArray);

public:
	// アニメーション
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* InAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OutAnim;

	// 決定ボタン
	UPROPERTY(meta = (BindWidget))
	UButton* DecideButton;

	// カードボックス
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox0;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox1;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox2;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox3;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox4;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox5;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox6;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox7;
	TArray<USizeBox*> CardBoxArray;

	// カードウィジェットクラス
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CardWidgetClass;

	// 選択中のカード
	TArray<UCardData*> SelectCards;

private:
	// 確定させたか
	bool bIsDecided = false;
	// Outアニメーション中か
	bool bIsPlayingOutAnim = false;
};
