// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
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
    void OnUpdate(float DeltaSec);

    // �A�N�V�����t�F�[�Y�ȊO�Ŕ�\���ɂ���UI�̕\������
    void SetVisibleExceptActionPhase(bool Visible);


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

    // ��D
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HandCardsWidgetClass;

    // �J�[�h�I��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> CardSelectWidgetClass;

public: /* �C���X�^���X�̃|�C���^ */
    // �C���X�^���X��������HUD�̃��X�g
    TArray<UHUDBase*> HUDList;

    // �X�e�[�W�N���A
    UPROPERTY()
    UStageClearWidget* StageClearWidget = nullptr;
    // �Q�[���I�[�o�[
    UPROPERTY()
    UUserWidget* GameOverWidget = nullptr;
    // ��D
    UPROPERTY()
    UHandCardsWidget* HandCardsWidget = nullptr;
    // �J�[�h�I��
    UPROPERTY()
    UCardSelectWidget* CardSelectWidget = nullptr;

public: /* Delegate */
    // �J�[�h�I��p�f���Q�[�g
    FOnSelectCard SelectCardDelegate;
    // �J�[�h�I�������p�f���Q�[�g
    FOnUnSelectCard UnSelectCardDelegate;
};
