#include "System/Phase/BattlePhase_CardSelect.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include <Character/MyPlayerController.h>
#include "Card/DeckManager.h"


// �t�F�[�Y�J�n��
void UBattlePhase_CardSelect::OnBegin()
{
	// �J�[�h�I���E�B�W�F�b�g�ƃJ�[�h�u�b�N�̕\��
	SetHidden(false);

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
	if (CardSelectWidget == nullptr)
		return;

	// �\���A�j���[�V����
	CardSelectWidget->PlayInAnimation();

	// �f�b�L�}�l�[�W���[����h���[
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		ADeckManager* DeckManager = MyGM->DeckManager;
		if (DeckManager == nullptr)
			return;

		// �J�[�h�E�B�W�F�b�g�̒ǉ�
		TArray<UCardData*> DrawCards = DeckManager->DrawCards();
		CardSelectWidget->CreateCardWidgets(DrawCards);
	}
}

void UBattlePhase_CardSelect::OnTick(float DeltaSec)
{
	if (RequestNextPhase != EBattlePhase::None)
		return;

	// �t�F�[�Y�؂�ւ�����
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
	if (CardSelectWidget == nullptr)
		return;

	// ����{�^���������ꂽ��A�I���A�j���[�V������҂��Ă���A�N�V�����t�F�[�Y�փ��N�G�X�g
	if (CardSelectWidget->GetIsDecided())
	{
		RequestNextPhase = EBattlePhase::Action;
	}
}

// �t�F�[�Y�I����
void UBattlePhase_CardSelect::OnExit() 
{
	// �J�[�h�I���E�B�W�F�b�g�ƃJ�[�h�u�b�N�̔�\��
	SetHidden(true);
}

void UBattlePhase_CardSelect::SetHidden(bool bHidden)
{
	// �J�[�h�I���E�B�W�F�b�g�̔�\��
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
		return;
	if (PlayerController->MainHUDWidget == nullptr)
		return;
	UCardSelectWidget* CardSelectWidget = PlayerController->MainHUDWidget->CardSelectWidget;
	if (CardSelectWidget == nullptr)
		return;

	ESlateVisibility Visibility = bHidden ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	CardSelectWidget->SetVisibility(Visibility);

	// �J�[�h�u�b�N�̔�\��
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
	{
		if (ACardBook* CardBook = MyGM->GetCardBook())
		{
			CardBook->SetActorHiddenInGame(bHidden);
		}
	}
}