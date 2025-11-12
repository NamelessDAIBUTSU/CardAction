// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/EnemyCharaBannerListWidget.h"
#include <Enemy/EnemyManager.h>
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Components/VerticalBoxSlot.h"
#include <Components/SizeBox.h>
#include "Blueprint/WidgetTree.h"

void UEnemyCharaBannerListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

// バナーの初期化
void UEnemyCharaBannerListWidget::InitializeBanner()
{
	if (CharaBannerWidgetClass == nullptr)
		return;

	// レベルに存在する敵のリストを取得
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->EnemyManager == nullptr)
			return;

		const auto& EnemyList = MyGM->EnemyManager->GetEnemyList();
		for (int i = 0; i < EnemyList.Num(); ++i)
		{
			// ウィジェットの生成
			UCharaBannerWidget* BannerWidget = CreateWidget<UCharaBannerWidget>(GetWorld(), CharaBannerWidgetClass);
			if (BannerWidget)
			{
				CharaBannerWidgets.Add(BannerWidget);

				// 時間差でInAnimを再生
				BannerWidget->PlayInAnim();
			
				USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
				SizeBox->SetHeightOverride(140.f);
				SizeBox->AddChild(BannerWidget);

				// VerticalBoxに登録
				if (VerticalBannerBox)
				{
					UVerticalBoxSlot* BoxSlot = Cast<UVerticalBoxSlot>(VerticalBannerBox->AddChildToVerticalBox(SizeBox));
					if (BoxSlot)
					{
						// カード間の余白を追加
						BoxSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

						
					}
					auto DesiredSize = BannerWidget->GetDesiredSize();
					auto DesiredSized = BannerWidget->GetDesiredSize();
				}
			}

			// 各種バナーを設定 & 表示
			CharaBannerWidgets[i]->Setup(EnemyList[i]);
			CharaBannerWidgets[i]->SetVisibility(ESlateVisibility::Visible);
		}

		// 余分のバナーは非表示
		for (int i = EnemyList.Num(); i < CharaBannerWidgets.Num(); ++i)
		{
			CharaBannerWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
