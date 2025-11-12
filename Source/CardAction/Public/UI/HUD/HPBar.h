// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/ProgressBar.h>
#include <Enemy/EnemyBase.h>
#include <Components/TextBlock.h>
#include "HPBar.generated.h"

UENUM(BlueprintType)
enum class EHPBarType : uint8
{
	Player      UMETA(DisplayName = "Player"),
	Enemy       UMETA(DisplayName = "Enemy"),
};

// HP取得用のデリゲート
DECLARE_DELEGATE_RetVal(int, FOnGetMaxHP);
DECLARE_DELEGATE_RetVal(int, FOnGetCurrentHP);


UCLASS()
class CARDACTION_API UHPBar : public UHUDBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void OnUpdateHPBar();

	// 初期設定
	void Setup(UWidgetComponent* OwnerComp, const FOnGetMaxHP& GetMaxHPFunc, const FOnGetCurrentHP& GetCurrentHPFunc);

	// レイアウトを変更
	void ChangeLayout(EHPBarType Type);


private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyHPText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerHPText = nullptr;

	// アニメーション
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* EnemyLayout;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PlayerLayout;

private:
	// 誰用か
	EHPBarType BarType;

	// HP取得用デリゲート
	FOnGetMaxHP OnGetMaxHP;
	FOnGetCurrentHP OnGetCurrentHP;

	// 自身を所有しているウィジェットコンポーネント
	UPROPERTY()
	TWeakObjectPtr<UWidgetComponent> OwnerWidgetComp;
};

