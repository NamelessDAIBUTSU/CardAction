// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MapWidget.h"
#include "Components/CanvasPanelSlot.h"
#include <Map/MapManager.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UMapWidget::SetupInfo()
{
	// �}�b�v�̃T�C�Y���擾
	if (GetWorld() == nullptr || GetWorld()->GetGameInstance() == nullptr)
		return;
	UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
	if (MapManager == nullptr || MapManager->GetCurrentMap() == nullptr)
		return;
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

	FVector2D Position = FVector2D::Zero();
	// ���������F�J�n�ʒu����Width�������X�e�[�W�ԋ��������炵���ʒu
	Position.X = StartPosX + StagePos.X * StageDistX;
	// ���������F
	Position.Y = StartPosY + StagePos.Y * StageDistY;

	// �X�e�[�W�E�B�W�F�b�g�̐���
	UStageWidget* NewStage = CreateWidget<UStageWidget>(GetWorld(), StageWidgetClass);
	if (NewStage == nullptr)
		return;

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
