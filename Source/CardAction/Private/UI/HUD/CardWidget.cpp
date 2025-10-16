// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardWidget.h"
#include <Components/TextBlock.h>
#include <Components/SizeBox.h>
#include <Character/MyPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "Animation/UMGSequencePlayer.h"

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

    AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (PlayerController == nullptr)
        return;
    if (PlayerController->MainHUDWidget == nullptr)
        return;
    UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
    if (CardSelectWidget == nullptr)
        return;

    // �I��
    if (bSelected == false)
    {
        // ��D���}�b�N�X�̏ꍇ�A�I���ł��Ȃ��悤�ɂ���
        if (CardSelectWidget->IsSelectMax())
            return;

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

            // �I��ԍ��e�L�X�g�̍X�V
            SetupSelectNum();
        }
    }
    // �I������
    else
    {
        if (Option.UnSelectCardDelegate.IsBound())
        {
            Option.UnSelectCardDelegate.Execute(CardData);

            // ���I���ɂ���
            bSelected = false;

            if (UnSelectAnim)
            {
                // �I�𒆗p�̃z�o�[�摜���\��
                UUMGSequencePlayer* SequencePlayer = PlayAnimation(UnSelectAnim);
                // �A�j���[�V�����I����A�ق��̑I�𒆂̃J�[�h�̑I��ԍ����X�V����
                if (SequencePlayer)
                {
                    SequencePlayer->OnSequenceFinishedPlaying().AddUObject(CardSelectWidget, &UCardSelectWidget::OnRefleshSelectNumText);
                }
            }
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

    // �f�[�^�����Ȃ甭������
    if (CardData == nullptr)
        return;

    // ���łɔ������͔�������
    if (IsAnimationPlaying(UseCardAnim))
        return;

    // ���ʔ���
    if (CardData->EffectClass)
    {
        if (UCardEffectBase* Effect = NewObject<UCardEffectBase>(this, CardData->EffectClass))
        {
            Effect->ExecuteEffect();
        }
    }

    // �A�j���[�V����
    if (UseCardAnim)
    {
        UUMGSequencePlayer* SequencePlayer = PlayAnimation(UseCardAnim);

        // �A�j���[�V�����I����
        if (SequencePlayer)
        {
            SequencePlayer->OnSequenceFinishedPlaying().AddLambda([this, &SequencePlayer](UUMGSequencePlayer& SeqPlayer)
                {
                    if (IsValid(this) == false)
                        return;

                    // �J�[�h�f�[�^�����Z�b�g
                    SetupCardData(nullptr);
                });
        }
    }
}

// �I��ԍ��e�L�X�g�̐ݒ�
void UCardWidget::SetupSelectNum()
{
    AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (PlayerController == nullptr)
        return;
    if (PlayerController->MainHUDWidget == nullptr)
        return;
    UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
    if (CardSelectWidget == nullptr)
        return;

    // �I��ԍ��X�V
    if (SelectNum && CardData)
    {
        int Index = CardSelectWidget->GetSelectIndex(CardData->UniqueID);

        FFormatNamedArguments Args;
        Args.Add(TEXT("Num"), Index);
        SelectNum->SetText(FText::Format(FTextFormat::FromString("{Num}"), Args));
    }
}

// �f�t�H���g�A�j���[�V�����ɖ߂�
void UCardWidget::PlayDefaultAnimation()
{
    if (DefaultAnim)
    {
        PlayAnimation(DefaultAnim);
    }
}
