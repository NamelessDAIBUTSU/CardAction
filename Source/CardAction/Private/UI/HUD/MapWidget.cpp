// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MapWidget.h"
#include "Components/CanvasPanelSlot.h"
#include <Map/MapManager.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <UI/HUD/StageLineWidget.h>

void UMapWidget::OnUpdate(float DeltaSec)
{
	for (UStageWidget* StageWidget : StageWidgets)
	{
		StageWidget->OnUpdate(DeltaSec);
	}
}

void UMapWidget::SetupInfo(UMapData* Data)
{
	if (Data == nullptr)
		return;
	MapData = Data;

	if (GetWorld() == nullptr || GetWorld()->GetGameInstance() == nullptr)
		return;
	UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr || MapManager->GetCurrentMap() == nullptr)
		return;

	// �}�b�v����ݒ�
	if (MapName)
	{
		MapName->SetText(FText::FromName(MapManager->GetCurrentMapName()));
	}
	// �w�b�_�[ / �t�b�^�[ / �x�[�X�摜��ݒ�
	if (HeaderImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->HeaderImage);
		HeaderImage->SetBrush(Brush);
	}
	if (FooterImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->FooterImage);
		FooterImage->SetBrush(Brush);
	}
	if (MapBaseImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->BaseImage);
		MapBaseImage->SetBrush(Brush);
	}

	// �}�b�v�̃T�C�Y���擾
	FVector2D MapSize = MapManager->GetCurrentMap()->GetSize();

	// �𑜓x�擾
	float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
	FVector2D ViewportSize;
	if (UGameViewportClient* Viewport = GetWorld()->GetGameViewport())
	{
		Viewport->GetViewportSize(ViewportSize);
	}
	// DPI�X�P�[�����l�����āA�␳�ςݘ_���l�ɕϊ�
	ViewportSize /= Scale;

	// �X�e�[�W�ԋ������Z�o
	StageDistX = (ViewportSize.X - OffsetX * 2.f) / MapSize.X;
	StageDistY = (ViewportSize.Y - OffsetY * 2.f) / MapSize.Y;

	// �����X�e�[�W��X���W
	StartPosX = OffsetX + StageDistX * 0.5f;
	// �����X�e�[�W��Y���W
	StartPosY = OffsetY + StageDistY * MapSize.Y * 0.5f;
}

// �L�����o�X�ɃX�e�[�W��ǉ�
void UMapWidget::CreateStageWidget(UStageObject* Stage)
{
	if (StageCanvas == nullptr)
		return;
	if (StageWidgetClass == nullptr || Stage == nullptr)
		return;

	FVector2D StagePos = Stage->GetPos();

	// �X�e�[�W�E�B�W�F�b�g�̈ʒu
	FVector2D Position = FVector2D::Zero();
	Position.X = StartPosX + StagePos.X * StageDistX;
	Position.Y = StartPosY + StagePos.Y * StageDistY * -1.f;

	// �X�e�[�W�E�B�W�F�b�g�̐���
	UStageWidget* NewStage = CreateWidget<UStageWidget>(GetWorld(), StageWidgetClass);
	if (NewStage == nullptr)
		return;
	StageWidgets.Add(NewStage);

	// �X�e�[�W���̐ݒ�
	NewStage->SetStageObject(Stage);

	// �z�u�ݒ�
	UCanvasPanelSlot* CanvasSlot = StageCanvas->AddChildToCanvas(NewStage);
	if (CanvasSlot)
	{
		// �����T�C�Y����
		CanvasSlot->SetAutoSize(true);                 
		// ������W�Ŕz�u
		CanvasSlot->SetPosition(Position);
		// �X���b�g�̒��S���킹
		CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	}

	// �X�e�[�W�󋵂ɍ��킹���A�j���[�V�����Đ�
	NewStage->PlayConditionAnim();
}

void UMapWidget::CreateStageLineWidget()
{
	if (StageLineWidgetClass == nullptr)
		return;

	for (UStageWidget* StageWidget : StageWidgets)
	{
		UStageObject* Stage = StageWidget->GetStageObject();
		if (Stage == nullptr)
			continue;

		for (UStageObject* ChainedStage : Stage->GetChainedStageList())
		{
			if (ChainedStage == nullptr)
				continue;

			// �O�X�e�[�W�E�B�W�F�b�g�̈ʒu���擾
			FVector2D StagePos = FVector2D::Zero();
			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(StageWidget->Slot))
			{
				StagePos = CanvasSlot->GetPosition();
			}

			// �X�e�[�W�Ԃ̕����擾
			FVector2D DistPos = (ChainedStage->GetPos() - Stage->GetPos()) * 0.5f;

			// �O�X�e�[�W�̈ʒu���畝���ړ�
			FVector2D LinePos = StagePos + FVector2D(StageDistX * DistPos.X, StageDistY * DistPos.Y * -1.f);

			// �X�e�[�W���C���E�B�W�F�b�g�𐶐�
			UStageLineWidget* NewLine = CreateWidget<UStageLineWidget>(GetWorld(), StageLineWidgetClass);
			if (NewLine == nullptr)
				return;

			// �z�u
			UCanvasPanelSlot* CanvasSlot = StageCanvas->AddChildToCanvas(NewLine);
			if (CanvasSlot)
			{
				// �����T�C�Y����
				CanvasSlot->SetAutoSize(true);
				// ������W�Ŕz�u
				CanvasSlot->SetPosition(LinePos);
				// �X���b�g�̒��S���킹
				CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));

				// �O�p�`�ɂ���cos�������߂Ċp�x�v�Z
				// #MEMO : cos�� = A^2 * B^2 / A�EB
				FVector2D A = LinePos - StagePos;
				FVector2D B = FVector2D(1.f, 0.f);
				float AngleRad = FMath::Acos(
					FVector2D::DotProduct(A.GetSafeNormal(), B.GetSafeNormal())
				);
				float AngleDeg = FMath::RadiansToDegrees(AngleRad);
				// ������ł���Ίp�x�𔽓]
				if (DistPos.Y > 0)
				{
					AngleDeg *= -1.f;
				}

				NewLine->SetRenderTransformAngle(AngleDeg);
			}
		}
	}
}
