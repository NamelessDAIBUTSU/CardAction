#pragma once

#include "CoreMinimal.h"
#include "CardTypeDef.generated.h"

// �J�[�h�̎��
UENUM(BlueprintType)
enum class ECardType : uint8
{
    Weapon    UMETA(DisplayName = "Weapon"),    // ����J�[�h
    Assist    UMETA(DisplayName = "Assist"),    // �A�V�X�g�J�[�h
};

// ����̎��
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Melee       UMETA(DisplayName = "Melee"),       // �ߐ�
    LongRange   UMETA(DisplayName = "LongRange"),   // ������
};

// �U������
UENUM(BlueprintType)
enum class EAttackElementType : uint8
{
    None        UMETA(DisplayName = "None"),    // ������
    Fire        UMETA(DisplayName = "Fire"),    // �Α���
    Thunder     UMETA(DisplayName = "Thunder"), // ������
};

// ���A���e�B
UENUM(BlueprintType)
enum class ECardRarity : uint8
{
    Common     UMETA(DisplayName = "Common"),
    Rare       UMETA(DisplayName = "Rare"),
    Epic       UMETA(DisplayName = "Epic"),
    Legendary  UMETA(DisplayName = "Legendary")
};