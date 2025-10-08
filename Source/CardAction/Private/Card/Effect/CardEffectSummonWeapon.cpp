#include "Card/Effect/CardEffectSummonWeapon.h"
#include <Kismet/GameplayStatics.h>
#include <Character/MyCharacter.h>

void UCardEffectSummonWeapon::ExecuteEffect()
{
	// プレイヤーに武器を装備させる
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
		return ;
	APawn* Pawn = PlayerController->GetPawn();
	if (Pawn == nullptr)
		return ;

	// プレイヤーキャラクターに装備させる
	AMyCharacter* Player = Cast<AMyCharacter>(Pawn);
	if (Player)
	{
		// 武器を生成
		AWeaponActorBase* WeaponActor = GetWorld()->SpawnActor<AWeaponActorBase>(Weapon);
		// プレイヤーに装備
		Player->EquipWeapon(WeaponActor);
	}
}
