// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/HorizontalBox.h>
#include <UI/HUD/CardWidget.h>
#include "Components/PanelSlot.h"
#include <Components/SizeBox.h>
#include "SelectedCardsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API USelectedCardsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// �I�𒆃J�[�h�ɒǉ�
	UFUNCTION()
	void AddToSelectedCards(UCardData* Data);

	UFUNCTION()
	void RemoveFromSelectedCards(UCardData* Data);

	// ����
	void OnExecute();

public:
	// ��D�̍ő吔
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	int MaxSelectedCardsNum = 3;

	// �J�[�h�N���X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> CardsWidgetClass;

	// �I�𒆃J�[�h�{�b�N�X
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* CardsHorizontalBox;

	// ���E�[�}�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Margin")
	FMargin EdgeMargin;
	// �J�[�h�ԃ}�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Margin")
	float Margin = 6.f;
};
