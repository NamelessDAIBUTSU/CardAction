#pragma once

#include "CoreMinimal.h"
#include "CardTypeDef.generated.h"

// カードの種類
UENUM(BlueprintType)
enum class ECardType : uint8
{
    Weapon    UMETA(DisplayName = "Weapon"),    // 武器カード
    Assist    UMETA(DisplayName = "Assist"),    // アシストカード
};

// 武器の種類
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Melee       UMETA(DisplayName = "Melee"),       // 近接
    LongRange   UMETA(DisplayName = "LongRange"),   // 遠距離
};

// 攻撃属性
UENUM(BlueprintType)
enum class EAttackElementType : uint8
{
    None        UMETA(DisplayName = "None"),    // 無属性
    Fire        UMETA(DisplayName = "Fire"),    // 火属性
    Thunder     UMETA(DisplayName = "Thunder"), // 雷属性
};

// レアリティ
UENUM(BlueprintType)
enum class ECardRarity : uint8
{
    Common     UMETA(DisplayName = "Common"),
    Rare       UMETA(DisplayName = "Rare"),
    Epic       UMETA(DisplayName = "Epic"),
    Legendary  UMETA(DisplayName = "Legendary")
};