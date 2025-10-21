// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FadeWidget.h"

void UFadeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �}�E�X�Ƃ̓����蔻���؂�
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

// �t�F�[�h����
void UFadeWidget::FadeIn(float InFadeSec)
{
	if (FadeMask == nullptr)
		return;

	CurrentFadeType = EFadeType::FadeIn;

	// ���݂̃A���t�@�l
	FadeMask->ColorAndOpacity.A = 1.f;
	float CurrentAlpha = FadeMask->ColorAndOpacity.A;
	// ���ω���
	float AmountOfAlpha = CurrentAlpha - 0.f;

	if (FMath::IsNearlyZero(InFadeSec))
	{
		FadeSpeed = AmountOfAlpha;
	}
	// ���t���[���̃��ω��ʂ��v�Z
	else
	{
		FadeSpeed = AmountOfAlpha / InFadeSec;
	}
}

void UFadeWidget::FadeOut(float OutFadeSec)
{
	if (FadeMask == nullptr)
		return;

	CurrentFadeType = EFadeType::FadeOut;
	SetVisibility(ESlateVisibility::Visible);

	// ���݂̃A���t�@�l
	FadeMask->ColorAndOpacity.A = 0.f;
	float CurrentAlpha = FadeMask->ColorAndOpacity.A;
	// ���ω���
	float AmountOfAlpha = 1.f - CurrentAlpha;

	// 0�b�w��̓X�s�[�h��MAX�ɂ���
	if (FMath::IsNearlyZero(OutFadeSec))
	{
		FadeSpeed = AmountOfAlpha;
	}
	// ���t���[���̃��ω��ʂ��v�Z
	else
	{
		FadeSpeed = AmountOfAlpha / OutFadeSec;
	}
}

// �t�F�[�h�X�V
void UFadeWidget::UpdateFade(float DeltaSec)
{
	if (FadeMask == nullptr)
		return;

	FLinearColor Color = FadeMask->GetColorAndOpacity();

	switch (CurrentFadeType)
	{
	case EFadeType::FadeIn:
		Color.A -= FadeSpeed * DeltaSec;
		Color.A = FMath::Max(0.f, Color.A);

		// �t�F�[�h�I��
		if (FMath::IsNearlyZero(Color.A))
		{
			CurrentFadeType = EFadeType::None;
		}

		break;
	case EFadeType::FadeOut:
		Color.A += FadeSpeed * DeltaSec;
		Color.A = FMath::Min(Color.A, 1.f);

		// �t�F�[�h�I��
		if (FMath::IsNearlyEqual(Color.A, 1.f))
		{
			CurrentFadeType = EFadeType::None;

			// �t�F�[�h�I����̃R�[���o�b�N����
			if (OnFadeOutFinished)
			{
				OnFadeOutFinished();
			}
		}
		break;
	default:
		break;
	}

	FadeMask->SetColorAndOpacity(Color);
}

// �t�F�[�h����
bool UFadeWidget::IsFade() 
{
	return IsFadeIn() || IsFadeOut(); 
}
bool UFadeWidget::IsFadeIn() 
{
	return CurrentFadeType == EFadeType::FadeIn; 
}
bool UFadeWidget::IsFadeOut() 
{
	return CurrentFadeType == EFadeType::FadeOut; 
}

// �t�F�[�h�I�����̃R�[���o�b�N�o�^
void UFadeWidget::SetOnFadeOutFinished(TFunction<void()> Func)
{
	OnFadeOutFinished = Func;
}

