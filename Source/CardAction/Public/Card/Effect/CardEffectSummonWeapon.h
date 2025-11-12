#pragma once
#include "CoreMinimal.h"
#include "Card/Effect/CardEffectBase.h"
#include "Weapon/WeaponBase.h"
#include "CardEffectSummonWeapon.generated.h"

UCLASS(BlueprintType)
class CARDACTION_API UCardEffectSummonWeapon : public UCardEffectBase
{
	GENERATED_BODY()

public:
	// 効果発動
	virtual void ExecuteEffect() override;

public:
	// 武器
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeaponActorBase> WeaponClass;
};
