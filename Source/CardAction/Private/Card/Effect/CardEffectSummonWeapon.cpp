#include "Card/Effect/CardEffectSummonWeapon.h"
#include <Kismet/GameplayStatics.h>
#include <Character/MyCharacter.h>
#include <System/MyGameMode.h>
#include "Grid/GridManager.h"

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
	if (Player && WeaponClass)
	{
		// 武器を生成
		AWeaponActorBase* WeaponActor = GetWorld()->SpawnActor<AWeaponActorBase>(WeaponClass, Player->GetActorLocation(), Player->GetActorRotation());
		if (WeaponActor)
		{
			// 所有者を設定
			WeaponActor->SetWeaponOwner(Player);

			// 生成時の座標を保存
			if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
			{
				if (MyGM->GridManager == nullptr)
					return;

				FCoord SpawnCoord = MyGM->GridManager->ConvertToGridCoord(Player->GetActorLocation());
				WeaponActor->SetSpawnCoord(SpawnCoord);
			}
		}
	}
}
