// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Card/CardData.h>
#include "Card/SelectCardDelegate.h"

#include "CardWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected: /* UUserWidget */
	virtual void NativeConstruct() override;


public:
	// ������
	void Initialize(UCardData* Data, FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate);
	// �E�B�W�F�b�g�̂ݏ�����
	void InitializeWidget(UCardData* Data);

	// �J�[�h�f�[�^�̎擾
	UCardData* GetCardData() const { return CardData; }

	// �}�E�X�C�x���g
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// ���ʔ���
	void ExecuteEffect();

private:
	// �J�[�h�f�[�^
	UPROPERTY(VisibleAnywhere, Category = "Data")
	UCardData* CardData = nullptr;

	// �I�𒆃J�[�h�ɒǉ�����f���Q�[�g
	FOnSelectCard SelectCardDelegate;
	// �I�𒆃J�[�h���珜������f���Q�[�g
	FOnUnSelectCard UnSelectCardDelegate;

	// �I�𒆂�
	bool bSelected = false;
};
