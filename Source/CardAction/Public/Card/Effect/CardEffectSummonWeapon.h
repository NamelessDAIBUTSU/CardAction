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
	// å¯â î≠ìÆ
	virtual void ExecuteEffect() override;

public:
	// ïêäÌ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeaponActorBase> WeaponClass;
};
