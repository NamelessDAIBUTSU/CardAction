// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include <Enemy/EnemyBase.h>
#include "EnemyHPBar.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UEnemyHPBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void OnUpdateHPBar();

	// 所有エネミーの設定
	void SetOwner(AEnemyBase* Enemy) { Owner = Enemy; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProgressBar* HPBar = nullptr;

private:
	// 所有エネミー
	AEnemyBase* Owner = nullptr;
};
