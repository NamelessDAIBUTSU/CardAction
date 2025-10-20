// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FadeWidget.h"

// フェード処理
void UFadeWidget::FadeIn(float InFadeSec)
{
	if (FadeMask == nullptr)
		return;

	CurrentFadeType = EFadeType::FadeIn;

	// 現在のアルファ値
	FadeMask->ColorAndOpacity.A = 1.f;
	float CurrentAlpha = FadeMask->ColorAndOpacity.A;
	// α変化量
	float AmountOfAlpha = CurrentAlpha - 0.f;

	if (FMath::IsNearlyZero(InFadeSec))
	{
		FadeSpeed = AmountOfAlpha;
	}
	// 毎フレームのα変化量を計算
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

	// 現在のアルファ値
	FadeMask->ColorAndOpacity.A = 0.f;
	float CurrentAlpha = FadeMask->ColorAndOpacity.A;
	// α変化量
	float AmountOfAlpha = 1.f - CurrentAlpha;

	// 0秒指定はスピードをMAXにする
	if (FMath::IsNearlyZero(OutFadeSec))
	{
		FadeSpeed = AmountOfAlpha;
	}
	// 毎フレームのα変化量を計算
	else
	{
		FadeSpeed = AmountOfAlpha / OutFadeSec;
	}
}

// フェード更新
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
		// フェード終了
		if (FMath::IsNearlyZero(Color.A))
		{
			CurrentFadeType = EFadeType::None;
		}

		break;
	case EFadeType::FadeOut:
		Color.A += FadeSpeed * DeltaSec;
		Color.A = FMath::Min(Color.A, 1.f);
		// フェード終了
		if (FMath::IsNearlyEqual(Color.A, 1.f))
		{
			CurrentFadeType = EFadeType::None;
		}

		break;
	default:
		break;
	}

	FadeMask->SetColorAndOpacity(Color);

	UE_LOG(LogTemp, Warning, TEXT("Alpha : %f"), Color.A);
}

// フェード中か
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

