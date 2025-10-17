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

// HP�擾�p�̃f���Q�[�g
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

	// �����ݒ�
	void Setup(UWidgetComponent* OwnerComp, const FOnGetMaxHP& GetMaxHPFunc, const FOnGetCurrentHP& GetCurrentHPFunc);

	// ���C�A�E�g��ύX
	void ChangeLayout(EHPBarType Type);


private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyHPText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerHPText = nullptr;

	// �A�j���[�V����
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* EnemyLayout;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PlayerLayout;

private:
	// �N�p��
	EHPBarType BarType;

	// HP�擾�p�f���Q�[�g
	FOnGetMaxHP OnGetMaxHP;
	FOnGetCurrentHP OnGetCurrentHP;

	// ���g�����L���Ă���E�B�W�F�b�g�R���|�[�l���g
	UPROPERTY()
	TWeakObjectPtr<UWidgetComponent> OwnerWidgetComp;
};

