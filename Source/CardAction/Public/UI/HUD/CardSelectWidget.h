// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/HUDBase.h"
#include <Components/Button.h>
#include "Components/SizeBox.h"
#include "CardSelectWidget.generated.h"


UCLASS()
class CARDACTION_API UCardSelectWidget : public UHUDBase
{
	GENERATED_BODY()
	
public:
	// ������
	virtual bool Initialize() override;

public: /* UHUDBase */
	// In�A�j���[�V�����̍Đ�
	virtual void PlayInAnim() override;

public:
	// ���莞�̃R�[���o�b�N
	UFUNCTION()
	void OnDecide();

	// �r�W�u���ύX���̃R�[���o�b�N
	UFUNCTION()
	void OnChangeVisibility(ESlateVisibility NextVisibility);
	UFUNCTION()
	void OnChangeIsDecided();

	// �A�N�V�����t�F�[�Y�ւ̑J�ڔ���
	bool GetIsDecided() const { return bIsDecided; }

	// �J�[�h�E�B�W�F�b�g�̐���
	void CreateCardWidgets(const TArray<class UCardData*>& CardDataArray);

	// �ő�܂őI�����Ă��邩
	bool IsSelectMax() const;

	// �Y���J�[�h�̏��Ԏ擾
	int GetSelectIndex(const FName& ID);

	// �I�𒆃J�[�h�̑I��ԍ��e�L�X�g�����t���b�V������
	void OnRefleshSelectNumText(UUMGSequencePlayer& Player);

public:
	// ����{�^��
	UPROPERTY(meta = (BindWidget))
	UButton* DecideSelectButton;

	// �J�[�h�{�b�N�X
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox0;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox1;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox2;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox3;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox4;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox5;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox6;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardBox7;
	TArray<USizeBox*> CardBoxArray;

	// �J�[�h�E�B�W�F�b�g�N���X
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CardWidgetClass;

private:
	// �I�𒆂̃J�[�h
	TArray<UCardData*> SelectCards;

	// �m�肳������
	bool bIsDecided = false;
	// Out�A�j���[�V��������
	bool bIsPlayingOutAnim = false;
};
