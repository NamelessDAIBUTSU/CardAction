// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/Button.h>
#include "Components/SizeBox.h"
#include "CardSelectWidget.generated.h"


UCLASS()
class CARDACTION_API UCardSelectWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// 初期化
	virtual bool Initialize() override;

public: /* UHUDBase */
	// Inアニメーションの再生
	virtual void PlayInAnim() override;

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

	// カードウィジェットの生成
	void CreateCardWidgets(const TArray<class UCardData*>& CardDataArray);

	// 最大まで選択しているか
	bool IsSelectMax() const;

	// 該当カードの順番取得
	int GetSelectIndex(const FName& ID);

	// 選択中カードの選択番号テキストをリフレッシュする
	void OnRefleshSelectNumText(UUMGSequencePlayer& Player);

public:
	// 決定ボタン
	UPROPERTY(meta = (BindWidget))
	UButton* DecideSelectButton;

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

private:
	// 選択中のカード
	TArray<UCardData*> SelectCards;

	// 確定させたか
	bool bIsDecided = false;
	// Outアニメーション中か
	bool bIsPlayingOutAnim = false;
};
