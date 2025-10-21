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

// �o�i�[�̏�����
void UEnemyCharaBannerListWidget::InitializeBanner()
{
	if (CharaBannerWidgetClass == nullptr)
		return;

	// ���x���ɑ��݂���G�̃��X�g���擾
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->EnemyManager == nullptr)
			return;

		const auto& EnemyList = MyGM->EnemyManager->GetEnemyList();
		for (int i = 0; i < EnemyList.Num(); ++i)
		{
			// �E�B�W�F�b�g�̐���
			UCharaBannerWidget* BannerWidget = CreateWidget<UCharaBannerWidget>(GetWorld(), CharaBannerWidgetClass);
			if (BannerWidget)
			{
				CharaBannerWidgets.Add(BannerWidget);

				// ���ԍ���InAnim���Đ�
				BannerWidget->PlayInAnim();
			
				USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
				SizeBox->SetHeightOverride(140.f);
				SizeBox->AddChild(BannerWidget);

				// VerticalBox�ɓo�^
				if (VerticalBannerBox)
				{
					UVerticalBoxSlot* BoxSlot = Cast<UVerticalBoxSlot>(VerticalBannerBox->AddChildToVerticalBox(SizeBox));
					if (BoxSlot)
					{
						// �J�[�h�Ԃ̗]����ǉ�
						BoxSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

						
					}
					auto DesiredSize = BannerWidget->GetDesiredSize();
					auto DesiredSized = BannerWidget->GetDesiredSize();
				}
			}

			// �e��o�i�[��ݒ� & �\��
			CharaBannerWidgets[i]->Setup(EnemyList[i]);
			CharaBannerWidgets[i]->SetVisibility(ESlateVisibility::Visible);
		}

		// �]���̃o�i�[�͔�\��
		for (int i = EnemyList.Num(); i < CharaBannerWidgets.Num(); ++i)
		{
			CharaBannerWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
