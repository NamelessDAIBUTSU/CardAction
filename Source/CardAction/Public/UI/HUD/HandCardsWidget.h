// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UI/HUD/CardWidget.h>
#include <Components/HorizontalBox.h>
#include "Card/SelectCardDelegate.h"

#include "HandCardsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UHandCardsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// �J�[�h�I���f���Q�[�g��ݒ�
	void SetSelectCardDelegate(FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate);

	// ��D�ɃJ�[�h��ǉ�
	void AddToHandCards(UCardData* CardData);

public:
	// ��D�̍ő吔
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HandCards")
	int MaxHandCardsNum = 5;

	// �J�[�h�N���X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> CardsWidgetClass;

	// ��D�̃{�b�N�X
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* CardsHorizontalBox;

private:
	// ��D
	UPROPERTY()
	TArray<UCardWidget*> HandCards;

	// �I�𒆃J�[�h�ɒǉ�����f���Q�[�g
	FOnSelectCard SelectCardDelegate;
	// �I����Ԃ���������f���Q�[�g
	FOnUnSelectCard UnSelectCardDelegate;
};
