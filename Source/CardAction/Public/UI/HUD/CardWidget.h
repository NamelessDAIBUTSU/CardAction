// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Card/CardData.h>
#include "Card/SelectCardDelegate.h"

#include "CardWidget.generated.h"

// �\���ӏ��ɂ���ď������Ⴄ�̂ŃI�v�V�����\����
USTRUCT()
struct CARDACTION_API FCardWidgetOption
{
	GENERATED_BODY()

public:
	// �I�����̏����f���Q�[�g
	FOnSelectCard SelectCardDelegate;
	// �I���������̏����f���Q�[�g
	FOnUnSelectCard UnSelectCardDelegate;

	// �}�E�X�I�[�o�[�\��
	bool bCanMouseOver = true;
	// �}�E�X�I�[�o�[�Ŋg�傷�邩
	bool bChangeScale = true;
	// �}�E�X�I�[�o�[�Ńc�[���`�b�v��\�����邩
	bool bShowToolTip = false;
};

UCLASS()
class CARDACTION_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected: /* UUserWidget */
	virtual void NativeConstruct() override;


public:
	// ������
	void Initialize(UCardData* Data, const FCardWidgetOption& WidgetOption);

	// �J�[�h�f�[�^�̐ݒ�
	void SetupCardData(UCardData* Data);

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

	FCardWidgetOption Option;

	// �I�𒆂�
	bool bSelected = false;
};
