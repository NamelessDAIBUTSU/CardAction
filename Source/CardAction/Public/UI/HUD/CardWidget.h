// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Card/CardData.h>
#include "Card/SelectCardDelegate.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
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
	bool bShowToolTip = true;
};

UCLASS()
class CARDACTION_API UCardWidget : public UHUDBase
{
	GENERATED_BODY()

protected: /* UUserWidget */
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	// ������
	void Initialize(UCardData* Data, const FCardWidgetOption& WidgetOption);

	// �J�[�h�f�[�^�̐ݒ�
	void SetupCardData(UCardData* Data);

	// �J�[�h�f�[�^�̎擾
	UCardData* GetCardData() const { return CardData; }

	// �}�E�X�C�x���g
	UFUNCTION()
	void OnCardClicked();
	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// ���ʔ���
	void ExecuteEffect();

	// �I��ԍ��e�L�X�g�̐ݒ�
	void SetupSelectNum();

	// �f�t�H���g�A�j���[�V�����ɖ߂�
	void PlayDefaultAnimation();

public:


private: /* Widget */
	// �����蔻��p�{�^��
	UPROPERTY(meta = (BindWidget))
	UButton* CardButton = nullptr;

	// �J�[�h�x�[�X
	UPROPERTY(meta = (BindWidget))
	UImage* CardBase = nullptr;
	// �J�[�h�C���X�g
	UPROPERTY(meta = (BindWidget))
	UImage* CardImage = nullptr;

	// �J�[�h�^�C�v�A�C�R��
	UPROPERTY(meta = (BindWidget))
	UImage* CardTypeIcon = nullptr;
	// �����^�C�v�A�C�R��
	UPROPERTY(meta = (BindWidget))
	UImage* ElementTypeIcon = nullptr;

	// ���O�e�L�X�g
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText = nullptr;

	// �_���[�W�e�L�X�g
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText = nullptr;

	// �I��ԍ��e�L�X�g
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectNum = nullptr;

private: /* �A�j���[�V���� */
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SelectAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* UnSelectAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* MouseOverAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* MouseReleaseAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* UseCardAnim;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* DefaultAnim;

private:
	// �J�[�h�f�[�^
	UPROPERTY(VisibleAnywhere, Category = "Data")
	UCardData* CardData = nullptr;

	// �\���I�v�V����
	FCardWidgetOption Option;

	// �I�𒆂�
	bool bSelected = false;
};
