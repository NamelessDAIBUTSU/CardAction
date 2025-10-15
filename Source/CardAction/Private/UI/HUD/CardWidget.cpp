// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardWidget.h"
#include <Components/TextBlock.h>
#include <Components/SizeBox.h>

void UCardWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (CardButton)
    {
        CardButton->OnClicked.AddDynamic(this, &UCardWidget::OnCardClicked);
    }
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
void UCardWidget::OnCardClicked()
{
    if (Option.bCanMouseOver == false)
        return;

    // �I��
    if (bSelected == false)
    {
        if (Option.SelectCardDelegate.IsBound())
        {
            Option.SelectCardDelegate.Execute(CardData);

            // �I�𒆂ɂ���
            bSelected = true;

            // �I�𒆗p�̃z�o�[�摜��\��
            if (SelectAnim)
            {
                PlayAnimation(SelectAnim);
            }
        }
    }
    // �I������
    else
    {
        Option.UnSelectCardDelegate.Execute(CardData);

        // ���I���ɂ���
        bSelected = false;

        // �I�𒆗p�̃z�o�[�摜���\��
        if (UnSelectAnim)
        {
            PlayAnimation(UnSelectAnim);
        }
    }
}

// �}�E�X�I�[�o�[��
void UCardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("Over"));

    if (Option.bCanMouseOver == false)
        return;

    // �X�P�[���ύX
    if (Option.bChangeScale && MouseOverAnim)
    {
        StopAnimation(MouseReleaseAnim);
        PlayAnimation(MouseOverAnim);
    }

    // �c�[���`�b�v�\��
    if (Option.bShowToolTip)
    {

    }
}

// �}�E�X�I�[�o�[���痣�ꂽ��
void UCardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("Leave"));

    if (Option.bCanMouseOver == false)
        return;

    // �X�P�[���ύX
    if (Option.bChangeScale && MouseReleaseAnim)
    {
        StopAnimation(MouseOverAnim);
        PlayAnimation(MouseReleaseAnim);
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