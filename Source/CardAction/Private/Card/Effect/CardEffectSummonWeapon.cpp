#include "Card/Effect/CardEffectSummonWeapon.h"
#include <Kismet/GameplayStatics.h>
#include <Character/MyCharacter.h>

void UCardEffectSummonWeapon::ExecuteEffect()
{
	// �v���C���[�ɕ���𑕔�������
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
		return ;
	APawn* Pawn = PlayerController->GetPawn();
	if (Pawn == nullptr)
		return ;

	// �v���C���[�L�����N�^�[�ɑ���������
	AMyCharacter* Player = Cast<AMyCharacter>(Pawn);
	if (Player)
	{
		// ����𐶐�
		AWeaponActorBase* WeaponActor = GetWorld()->SpawnActor<AWeaponActorBase>(Weapon);
		// �v���C���[�ɑ���
		Player->EquipWeapon(WeaponActor);
	}
}
