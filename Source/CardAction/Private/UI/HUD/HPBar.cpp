// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HPBar.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

void UHPBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHPBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// ビルボード制御
	if (OwnerWidgetComp.IsValid())
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		if (CameraManager)
		{
			FVector CamLoc = CameraManager->GetCameraLocation();
			FVector CompLoc = OwnerWidgetComp->GetComponentLocation();

			// カメラへの方向を取得
			FVector ToCam = CamLoc - CompLoc;
			// 上下成分を無視して常に水平に
			ToCam.Z = 0.f;

			FRotator LookAtRot = ToCam.Rotation();
			LookAtRot.Yaw = 180.f;
			OwnerWidgetComp->SetWorldRotation(LookAtRot);
		}
	}

	// HPバーの更新
	OnUpdateHPBar();
}

void UHPBar::OnUpdateHPBar()
{
	if (HPBar == nullptr)
		return;
	if (OnGetMaxHP.IsBound() == false || OnGetCurrentHP.IsBound() == false)
		return;

	int MaxHP = OnGetMaxHP.Execute();
	int CurrentHP = OnGetCurrentHP.Execute();

	// 0除算回避
	if (OnGetMaxHP.Execute() == 0)
		return;

	// ゲージ更新
	float Rate = CurrentHP / (float)MaxHP;
	HPBar->SetPercent(Rate);

	// テキスト更新
	UTextBlock* Text = nullptr;
	switch (BarType)
	{
	case EHPBarType::Player:
		Text = PlayerHPText;
		break;
	case EHPBarType::Enemy:
		Text = EnemyHPText;
		break;
	default:
		break;
	}

	if (Text)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("HP"), CurrentHP);
		Text->SetText(FText::Format(FTextFormat::FromString("{HP}"), Args));
	}
}

// 初期設定
void UHPBar::Setup(UWidgetComponent* OwnerComp, const FOnGetMaxHP& GetMaxHPFunc, const FOnGetCurrentHP& GetCurrentHPFunc)
{
	OwnerWidgetComp = OwnerComp;

	OnGetMaxHP = GetMaxHPFunc;
	OnGetCurrentHP = GetCurrentHPFunc;
}

// レイアウトを変更
void UHPBar::ChangeLayout(EHPBarType Type)
{
	BarType = Type;

	switch (BarType)
	{
	case EHPBarType::Player:
		PlayAnimation(PlayerLayout);
		break;
	case EHPBarType::Enemy:
		PlayAnimation(EnemyLayout);
		break;
	default:
		break;
	}
}
