// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSlotWidget.h"
#include <Card/CardData.h>
#include <UI/HUD/CardWidget.h>
#include <Components/SizeBoxSlot.h>

void UCardSlotWidget::NativeConstruct()
{
	// �J�[�h�E�B�W�F�b�g�̐���
	if (CardWidgetClass)
	{
		CardWidget = CreateWidget<UCardWidget>(GetWorld(), CardWidgetClass);
		CardWidget->SetVisibility(ESlateVisibility::Hidden);

		// �J�[�h���{�b�N�X�ɔz�u
		if (CardBox)
		{
			if (USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardBox->AddChild(CardWidget)))
			{

			}
		}
	}
}

// �X���b�g�ԍ��̐ݒ�
void UCardSlotWidget::SetupSlotNum(int Num)
{
	if (SlotNum == nullptr)
		return;

	FFormatNamedArguments Args;
	Args.Add(TEXT("Num"), Num);
	SlotNum->SetText(FText::Format(FTextFormat::FromString("{Num}"), Args));
}

// �X���b�g�ɃJ�[�h����ݒ�
void UCardSlotWidget::SetupCardSlot(UCardData* Data)
{
	if (CardWidget)
	{
		// �J�[�h�f�[�^��n��
		CardWidget->SetupCardData(Data);

		// �\���ݒ�
		if (Data == nullptr)
		{
			CardWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			CardWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

// �J�[�h�I���A�j���[�V�����Đ�
void UCardSlotWidget::PlaySelectAnim()
{
	if (bIsSelected == false && SelectAnim)
	{
		PlayAnimation(SelectAnim);
		bIsSelected = true;
	}
}
// �J�[�h�I�������A�j���[�V�����Đ�
void UCardSlotWidget::PlayUnSelectAnim()
{
	if (bIsSelected && UnSelectAnim)
	{
		PlayAnimation(UnSelectAnim);
		bIsSelected = false;
	}
}

// ���ʔ���
void UCardSlotWidget::ExecuteEffect()
{
	if (CardWidget)
	{
		CardWidget->ExecuteEffect();
	}
}