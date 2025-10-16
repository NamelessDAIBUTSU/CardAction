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
	// ���ʔ���
	virtual void ExecuteEffect() override;

public:
	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeaponActorBase> WeaponClass;
};
