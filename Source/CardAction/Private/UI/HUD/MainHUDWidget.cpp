// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MainHUDWidget.h"
#include "Components/CanvasPanelSlot.h"
#include <Components/WidgetComponent.h>

// ������
void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

    SelectCardDelegate.BindUObject(this, &UMainHUDWidget::OnAddToSelectedCards);
    UnSelectCardDelegate.BindUObject(this, &UMainHUDWidget::OnRemoveFromSelectedCards);

    // �E�B�W�F�b�g�̐���
    {
        // �Q�[���N���A
        if (GameClearWidgetClass)
        {
            GameClearWidget = CreateWidget<UUserWidget>(GetWorld(), GameClearWidgetClass);

            // �L�����o�X�ɒǉ�
            if (MainCanvas)
            {
                MainCanvas->AddChild(GameClearWidget);
            }
        }

        // �Q�[���I�[�o�[
        if (GameOverWidgetClass)
        {
            GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);

            // �L�����o�X�ɒǉ�
            if (MainCanvas)
            {
                MainCanvas->AddChild(GameOverWidget);
            }
        }

        // HP�Q�[�W
        if (HPGaugeWidgetClass)
        {
            UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), HPGaugeWidgetClass);
            HPGaugeWidget = Cast<UHPGauge>(widget);

            // �L�����o�X�ɒǉ�
            if (MainCanvas)
            {
                MainCanvas->AddChild(HPGaugeWidget);
            }
        }

        // ��D
        if (HandCardsWidgetClass)
        {
            HandCardsWidget = CreateWidget<UHandCardsWidget>(GetWorld(), HandCardsWidgetClass);
            if (HandCardsWidget)
            {
                HandCardsWidget->SetSelectCardDelegate(SelectCardDelegate, UnSelectCardDelegate);

                // �L�����o�X�ɒǉ�
                if (MainCanvas)
                {
                    MainCanvas->AddChild(HandCardsWidget);

                    // �����ɔz�u
                    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HandCardsWidget->Slot);
                    if (CanvasSlot)
                    {
                        CanvasSlot->SetAnchors(FAnchors(0.f, 0.f));           //����
                        CanvasSlot->SetAlignment(FVector2D(0.f, 0.f));       // ����
                        CanvasSlot->SetPosition(FVector2D(0.f, 0.f));     // 50px�E�A50px��
                    }
                    HandCardsWidget->SetRenderScale(FVector2D(1.f, 1.f));
                }
            }
        }

        // �I�𒆃J�[�h
        if (SelectedCardsWidgetClass)
        {
            SelectedCardsWidget = CreateWidget<USelectedCardsWidget>(GetWorld(), SelectedCardsWidgetClass);
            // �L�����o�X�ɒǉ�
            if (MainCanvas)
            {
                MainCanvas->AddChild(SelectedCardsWidget);

                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SelectedCardsWidget->Slot);
                if (CanvasSlot)
                {
                    // �^�񒆉�
                    CanvasSlot->SetAnchors(FAnchors(0.5f, 1.f));
                    CanvasSlot->SetAlignment(FVector2D(0.5f, 1.f));
                }
                //SelectedCardsWidget->SetRenderScale(FVector2D(0.75f, 0.75f));
            }
        }
    }

}

// �X�V
void UMainHUDWidget::OnTick(float InDeltaTime)
{
    if (HPGaugeWidget)
    {
        HPGaugeWidget->OnUpdateHPGauge();
    }
}

// �I�𒆃J�[�h�ɒǉ�
void UMainHUDWidget::OnAddToSelectedCards(UCardData* CardData)
{
    if (SelectedCardsWidget)
    {
        SelectedCardsWidget->AddToSelectedCards(CardData);
    }
}

void UMainHUDWidget::OnRemoveFromSelectedCards(UCardData* CardData)
{
    if (SelectedCardsWidget)
    {
        SelectedCardsWidget->RemoveFromSelectedCards(CardData);
    }
}
