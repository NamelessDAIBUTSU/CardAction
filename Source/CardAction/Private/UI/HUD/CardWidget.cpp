// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardWidget.h"
#include <Components/TextBlock.h>
#include <Components/SizeBox.h>

void UCardWidget::NativeConstruct()
{
}

void UCardWidget::SetupCardData(UCardData* Data)
{
    CardData = Data;

    if (CardData == nullptr)
        return;

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

void UCardWidget::Initialize(UCardData* Data, const FCardWidgetOption& WidgetOption)
{
    // �E�B�W�F�b�g�̏�����
    SetupCardData(Data);

    // �\���I�v�V�����̐ݒ�
    Option = WidgetOption;
}

// �N���b�N��
FReply UCardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (Option.bCanMouseOver == false)
        return FReply::Unhandled();

    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        // �I��
        if (bSelected == false)
        {
            if (Option.SelectCardDelegate.IsBound())
            {
                Option.SelectCardDelegate.Execute(CardData);

                // �I�𒆂ɂ���
                bSelected = true;

                // �I�𒆗p�̃z�o�[�摜��\��

            }
        }
        // �I������
        else
        {
            Option.UnSelectCardDelegate.Execute(CardData);

            // ���I���ɂ���
            bSelected = false;

            // �I�𒆗p�̃z�o�[�摜���\��
            
        }

        return FReply::Handled();
    }
    return FReply::Unhandled();
}

// �}�E�X�I�[�o�[��
void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (Option.bCanMouseOver == false)
        return;

    // �X�P�[���ύX
    if (Option.bChangeScale)
    {
        this->SetRenderScale(FVector2D(1.2f, 1.2f));
    }

    // �c�[���`�b�v�\��
    if (Option.bShowToolTip)
    {

    }
}

// �}�E�X�I�[�o�[���痣�ꂽ��
void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    if (Option.bCanMouseOver == false)
        return;

    // �X�P�[���ύX
    if (Option.bChangeScale)
    {
        this->SetRenderScale(FVector2D(1.f, 1.f));
    }

    // �c�[���`�b�v��\��
    if (Option.bShowToolTip)
    {

    }
}

// ���ʔ���
void UCardWidget::ExecuteEffect()
{
    if (IsValid(this) == false)
    {
        UE_LOG(LogTemp, Error, TEXT("this is not valid"));
        return;
    }

    if (CardData && CardData->EffectClass)
    {
        UCardEffectBase* Effect = NewObject<UCardEffectBase>(this, CardData->EffectClass);
        if (Effect)
        {
            Effect->ExecuteEffect();
        }
    }
}