#pragma once

#include "CoreMinimal.h"
#include "CardTypeDef.generated.h"

// ��D�̍ő吔
#define MAX_HAND_CARDS_NUM 4
// �f�b�L��������Ă���J�[�h�̖���
#define DRAW_CARDS_NUM 8

// �J�[�h�̎��
UENUM(BlueprintType)
enum class ECardType : uint8
{
    Weapon      UMETA(DisplayName = "Weapon"),    // ����J�[�h
    Assist      UMETA(DisplayName = "Assist"),    // �A�V�X�g�J�[�h
    Guardian    UMETA(DisplayName = "Guardian"),  // �K�[�f�B�A���J�[�h
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
    Water       UMETA(DisplayName = "Water"),   // ������
};

// ���A���e�B
UENUM(BlueprintType)
enum class ECardRarityType : uint8
{
    Common      UMETA(DisplayName = "Common"),
    Rare        UMETA(DisplayName = "Rare"),
    Epic        UMETA(DisplayName = "Epic"),
    Legendary   UMETA(DisplayName = "Legendary"),
    Mithic      UMETA(DisplayName = "Mithic")
};