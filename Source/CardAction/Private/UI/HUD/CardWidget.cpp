// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardWidget.h"
#include <Components/TextBlock.h>
#include <Components/SizeBox.h>

void UCardWidget::NativeConstruct()
{
}

void UCardWidget::InitializeWidget(UCardData* Data)
{
    if (Data == nullptr)
        return;

    CardData = Data;

    // �e�L�X�g�̐ݒ�
    // ���O
    UTextBlock* NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
    if (NameText)
    {
        NameText->SetText(FText::FromName(CardData->Name));
    }
    // ����
    UTextBlock* DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));
    if (DescText)
    {
        DescText->SetText(FText::FromString(CardData->Description));

        // �������s��L����
        DescText->SetAutoWrapText(true);      
        USizeBox* SizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("TextBox")));
    }
}

void UCardWidget::Initialize(UCardData* Data, FOnSelectCard SelectDelegate, FOnUnSelectCard UnSelectDelegate)
{
    // �E�B�W�F�b�g�̏�����
    InitializeWidget(Data);

    // �f���Q�[�g�̐ݒ�
    SelectCardDelegate = SelectDelegate;
    UnSelectCardDelegate = UnSelectDelegate;
}

FReply UCardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        // ���I���̏ꍇ�A�I�𒆃J�[�h�ɒǉ�
        if (bSelected == false)
        {
            if (SelectCardDelegate.IsBound())
            {
                SelectCardDelegate.Execute(CardData);

                // �I�𒆂ɂ���
                bSelected = true;

                // �I�𒆗p�̃z�o�[�摜��\��

            }
        }
        // �I�𒆂̏ꍇ�A�I�𒆃J�[�h����O���ēx�I���\�ɂ���
        else
        {
            UnSelectCardDelegate.Execute(CardData);

            // ���I���ɂ���
            bSelected = false;

            // �I�𒆗p�̃z�o�[�摜���\��
            
        }

        return FReply::Handled();
    }
    return FReply::Unhandled();
}

void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // �I�𒆂̃J�[�h�͑I���ł��Ȃ��悤����
    if (bSelected)
        return;
 
    this->SetRenderScale(FVector2D(1.2f, 1.2f));
}

void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    this->SetRenderScale(FVector2D(1.f, 1.f));
}

// ���ʔ���
void UCardWidget::ExecuteEffect()
{
    if (CardData && CardData->Effect)
    {
        UCardEffectBase* Effect = NewObject<UCardEffectBase>(this, CardData->Effect);
        if (Effect)
        {
            Effect->ExecuteEffect();
        }
    }
}