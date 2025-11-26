#pragma once

#include "CoreMinimal.h"
#include "CardTypeDef.generated.h"

// 手札の最大数
#define MAX_HAND_CARDS_NUM 4
// デッキから引いてくるカードの枚数
#define DRAW_CARDS_NUM 8

// カードの種類
UENUM(BlueprintType)
enum class ECardType : uint8
{
    Weapon      UMETA(DisplayName = "Weapon"),    // 武器カード
    Assist      UMETA(DisplayName = "Assist"),    // アシストカード
    Guardian    UMETA(DisplayName = "Guardian"),  // ガーディアンカード
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
    None        UMETA(DisplayName = "無属性"),     // 無属性
    Fire        UMETA(DisplayName = "火属性"),     // 火属性
    Thunder     UMETA(DisplayName = "雷属性"),     // 雷属性
    Water       UMETA(DisplayName = "水属性"),     // 水属性
    Wind        UMETA(DisplayName = "風属性"),     // 風属性
};

// レアリティ
UENUM(BlueprintType)
enum class ECardRarityType : uint8
{
    Common      UMETA(DisplayName = "コモン"),
    Rare        UMETA(DisplayName = "レア"),
    Epic        UMETA(DisplayName = "エピック"),
    Legendary   UMETA(DisplayName = "レジェンダリー"),
    Mithic      UMETA(DisplayName = "ミシック")
};