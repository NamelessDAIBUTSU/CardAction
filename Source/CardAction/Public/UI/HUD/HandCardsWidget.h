// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <UI/HUD/CardWidget.h>
#include <UI/HUD/CardSlotWidget.h>
#include <Components/HorizontalBox.h>
#include "Card/SelectCardDelegate.h"

#include "HandCardsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UHandCardsWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// ������
	virtual void NativeConstruct() override;

public:
	// �J�[�h�I���f���Q�[�g��ݒ�
	void SetSelectCardDelegate(FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate);

	// ��D�ɃJ�[�h��ǉ�
	void AddToHandCards(int Index, UCardData* CardData);

	// ��D�J�[�h�����Z�b�g
	void ResetHandCards();
	void ResetHandCards(int Index);

	// �J�[�h�I��
	void SelectCard(int SelectIndex);

	// �J�[�h�̌��ʔ���
	void ExecuteEffect(int Index);

	// �J�[�h�E�B�W�F�b�g�̃A�j���[�V�������f�t�H���g�ɖ߂�
	void PlayDefaultAnimation(int Index);

public:
	// �J�[�h�X���b�g�N���X
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CardSlotWidgetClass;

	// ��D�̃{�b�N�X
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* CardsHorizontalBox;

private:
	// ��D
	UPROPERTY(VisibleAnywhere)
	TArray<UCardSlotWidget*> HandCards;

	// �I�𒆃J�[�h�ɒǉ�����f���Q�[�g
	FOnSelectCard SelectCardDelegate;
	// �I����Ԃ���������f���Q�[�g
	FOnUnSelectCard UnSelectCardDelegate;
};
