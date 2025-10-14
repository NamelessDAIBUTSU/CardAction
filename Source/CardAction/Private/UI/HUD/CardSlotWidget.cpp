// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSlotWidget.h"
#include <Card/CardData.h>
#include <UI/HUD/CardWidget.h>
#include <Components/SizeBoxSlot.h>

// �X���b�g�ԍ��̐ݒ�
void UCardSlotWidget::SetupSlotNum(int Num)
{
	if (SlotNum == nullptr)
		return;

	FFormatNamedArguments Args;
	Args.Add(TEXT("Num"), Num);
	SlotNum->SetText(FText::Format(FTextFormat::FromString("{Num}"), Args));
}

// �X���b�g�ɃJ�[�h��ݒ�
void UCardSlotWidget::SetupCardSlot(UCardData* Data)
{
	// �J�[�h�E�B�W�F�b�g�̐���
	if (CardWidgetClass)
	{
		CardWidget = CreateWidget<UCardWidget>(GetWorld(), CardWidgetClass);
		if (CardWidget)
		{
			CardWidget->InitializeWidget(Data);
		}

		// �J�[�h���{�b�N�X�ɔz�u
		if (CardBox)
		{
			USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardBox->AddChild(CardWidget));
		}
	}
}

// �J�[�h�I���A�j���[�V�����Đ�
void UCardSlotWidget::PlaySelectAnim()
{
	if (SelectAnim)
	{
		PlayAnimation(SelectAnim);
		bIsSelected = true;
	}
}
// �J�[�h�I�������A�j���[�V�����Đ�
void UCardSlotWidget::PlayUnSelectAnim()
{
	if (UnSelectAnim)
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