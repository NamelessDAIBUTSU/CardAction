// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "FadeWidget.generated.h"

// �t�F�[�h�̎��
UENUM(BlueprintType)
enum class EFadeType : uint8
{
	None    UMETA(DisplayName = "None"),
	FadeIn  UMETA(DisplayName = "FadeIn"),
	FadeOut UMETA(DisplayName = "FadeOut"),
};

UCLASS()
class CARDACTION_API UFadeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// �t�F�[�h����
	void FadeIn(float InFadeSec = 1.f);
	void FadeOut(float OutFadeSec = 1.f);

	// �t�F�[�h�X�V
	void UpdateFade(float DeltaSec);

	// �t�F�[�h����
	bool IsFade();
	bool IsFadeIn();
	bool IsFadeOut();

private:
	// �t�F�[�h����E�B�W�F�b�g
	UPROPERTY(meta = (BindWidget))
	UImage* FadeMask;

	// �t�F�[�h�X�V���ԗp
	float ElapsedSec = 0.f;

	// ���t���[���̃t�F�[�h�ω���
	float FadeSpeed = 0.f;

	// ���݂̃t�F�[�h�^�C�v
	EFadeType CurrentFadeType = EFadeType::None;
};
