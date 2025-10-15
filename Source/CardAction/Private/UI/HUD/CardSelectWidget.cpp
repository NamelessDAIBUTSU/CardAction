// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CardSelectWidget.h"
#include "Animation/WidgetAnimationEvents.h"
#include <Card/CardData.h>
#include <UI/HUD/CardWidget.h>
#include <Components/SizeBoxSlot.h>
#include <Kismet/GameplayStatics.h>
#include <Character/MyPlayerController.h>

// ������
bool UCardSelectWidget::Initialize()
{
    if (Super::Initialize() == false)
        return false;

    // ���莞�̃R�[���o�b�N�o�^
    if (DecideButton)
    {
        DecideButton->OnClicked.AddDynamic(this, &UCardSelectWidget::OnDecide);
    }

    // Hidden��Visible�ɕς�����Ƃ��Ƀt���O������������
    OnVisibilityChanged.AddDynamic(this, &UCardSelectWidget::OnChangeVisibility);

    // �J�[�h�{�b�N�X�E�B�W�F�b�g��z��ɂ����
    CardBoxArray.Add(CardBox0);
    CardBoxArray.Add(CardBox1);
    CardBoxArray.Add(CardBox2);
    CardBoxArray.Add(CardBox3);
    CardBoxArray.Add(CardBox4);
    CardBoxArray.Add(CardBox5);
    CardBoxArray.Add(CardBox6);
    CardBoxArray.Add(CardBox7);

    return true;
}

void UCardSelectWidget::OnDecide()
{
    if (OutAnim)
    {
        bIsPlayingOutAnim = true;

        // �o�C���h����
        UnbindAllFromAnimationFinished(OutAnim);

        // Out�A�j���[�V�������Đ�
        StopAnimation(OutAnim); 
        PlayAnimation(OutAnim);

        // �A�j���[�V�����I�����Ɋm��t���O�𗧂Ă�悤�R�[���o�b�N�o�^
        FWidgetAnimationDynamicEvent Delegate;
        Delegate.BindUFunction(this, FName("OnChangeIsDecided"));
        BindToAnimationFinished(OutAnim, Delegate);

        UE_LOG(LogTemp, Warning, TEXT("OnDecide"));
    }
}

// �r�W�u���ύX���̃R�[���o�b�N
void UCardSelectWidget::OnChangeVisibility(ESlateVisibility NextVisibility)
{
    if (NextVisibility == ESlateVisibility::Visible)
    {
        bIsDecided = false;

        // �I�𒆃J�[�h�̔z���������
        for (int i = SelectCards.Num() - 1; i >= 0; --i)
        {
            SelectCards.RemoveAt(i);
        }

        // ��D�J�[�h��������
        AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
        if (PlayerController == nullptr)
            return;
        if (PlayerController->MainHUDWidget == nullptr)
            return;
        UHandCardsWidget* HandCardsWidget = PlayerController->MainHUDWidget->HandCardsWidget;
        if (HandCardsWidget == nullptr)
            return;
        HandCardsWidget->ResetHandCards();
    }
}

void UCardSelectWidget::OnChangeIsDecided()
{
    if (bIsPlayingOutAnim == false)
        return;

    bIsDecided = true;
    bIsPlayingOutAnim = false;

    // �I�𒆂̃J�[�h����D�ɉ�����
    {
        AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
        if (PlayerController == nullptr)
            return;
        if (PlayerController->MainHUDWidget == nullptr)
            return;
        UHandCardsWidget* HandCardsWidget = PlayerController->MainHUDWidget->HandCardsWidget;
        if (HandCardsWidget == nullptr)
            return;

        for (int i = 0; i < SelectCards.Num(); ++i)
        {
            HandCardsWidget->AddToHandCards(i, SelectCards[i]);
        }

        // �󂪂����nullptr��ݒ�
        for (int i = SelectCards.Num(); i < MAX_HAND_CARDS_NUM; ++i)
        {
            HandCardsWidget->AddToHandCards(i, nullptr);
        }
    }
}

void UCardSelectWidget::PlayInAnimation()
{
    if (InAnim)
    {
        StopAnimation(InAnim);
        PlayAnimation(InAnim);
    }
}

// �J�[�h�E�B�W�F�b�g�̐���
void UCardSelectWidget::CreateCardWidgets(const TArray<UCardData*>& CardDataArray)
{
    if (CardWidgetClass == nullptr)
        return;

    for (int i = 0; i < CardDataArray.Num(); ++i)
    {
        // ����Ȃ��z�肾���ǁA�J�[�h�{�b�N�X�����݂��Ȃ������甲����
        if (CardBoxArray.Num() <= i || CardBoxArray[i] == nullptr)
            break;

        // �J�[�h�E�B�W�F�b�g�̐���
        UCardWidget* CardWidget = CreateWidget<UCardWidget>(GetWorld(), CardWidgetClass);
        if (CardWidget == nullptr)
            return;

        // �J�[�h�f�[�^��������
        {
            FCardWidgetOption Option;
            Option.bChangeScale = false;

            // �f���Q�[�g�ɑI���J�[�h�z��̍X�V�̏���������
            Option.SelectCardDelegate.BindLambda([this](UCardData* CardData)
                {
                    if (IsValid(this) == false)
                        return;
                    if (SelectCards.Num() >= MAX_HAND_CARDS_NUM)
                        return;
                    if (CardData == nullptr)
                        return;

                    SelectCards.Add(CardData);
                });
            Option.UnSelectCardDelegate.BindLambda([this](UCardData* CardData)
                {
                    if (IsValid(this) == false)
                        return;
                    if (CardData == nullptr)
                        return;

                    SelectCards.Remove(CardData);
                });

            CardWidget->Initialize(CardDataArray[i], Option);
        }

        // �T�C�Y�{�b�N�X�ɒǉ�
        CardBoxArray[i]->RemoveChildAt(0);
        if (USizeBoxSlot* BoxSlot = Cast<USizeBoxSlot>(CardBoxArray[i]->AddChild(CardWidget)))
        {
        }
    }
}
