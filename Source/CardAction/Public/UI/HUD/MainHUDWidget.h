// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "UI/HUD/SelectedCardsWidget.h"
#include "UI/HUD/HPGauge.h"
#include "UI/HUD/HandCardsWidget.h"
#include "UI/HUD/StageClearWidget.h"
#include "CardSelectWidget.h"
#include "Card/SelectCardDelegate.h"

#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected: /* UUserWidget */
    // ������
    virtual void NativeConstruct() override;

public:
    void OnTick(float DeltaTime);


private: /* Callback */
    // �I�𒆃J�[�h�ɒǉ�
    void OnAddToSelectedCards(UCardData* CardData);
    // �I�𒆃J�[�h������
    void OnRemoveFromSelectedCards(UCardData* CardData);
	

public: /* ��������Widget�N���X */
    // CanvasPanel���o�C���h
    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* MainCanvas;

    // �X�e�[�W�N���A
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> StageClearWidgetClass;

    // �Q�[���I�[�o�[
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    // HP�Q�[�W
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HPGaugeWidgetClass;

    // ��D
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HandCardsWidgetClass;

    // �I�𒆃J�[�h
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> SelectedCardsWidgetClass;

    // �J�[�h�I��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> CardSelectWidgetClass;


public: /* �C���X�^���X�̃|�C���^ */
    // �X�e�[�W�N���A
    UPROPERTY()
    UStageClearWidget* StageClearWidget = nullptr;
    // �Q�[���I�[�o�[
    UPROPERTY()
    UUserWidget* GameOverWidget = nullptr;
    // HP�Q�[�W
    UPROPERTY()
    UHPGauge* HPGaugeWidget = nullptr;
    // ��D
    UPROPERTY()
    UHandCardsWidget* HandCardsWidget = nullptr;
    // �I�𒆃J�[�h
    UPROPERTY()
    USelectedCardsWidget* SelectedCardsWidget = nullptr;
    // �J�[�h�I��
    UPROPERTY()
    UCardSelectWidget* CardSelectWidget = nullptr;


public: /* Delegate */
    // �J�[�h�I�����̃f���Q�[�g
    FOnSelectCard SelectCardDelegate;
    // �I����Ԃ���������f���Q�[�g
    FOnUnSelectCard UnSelectCardDelegate;
};
