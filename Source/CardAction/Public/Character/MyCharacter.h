// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputAction.h>
#include <Weapon/WeaponBase.h>
#include <Card/CardData.h>
#include "MyComponents/GridMovementComponent.h"
#include "MyCharacter.generated.h"

UCLASS(Blueprintable)
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	// ���̓o�C���h�ݒ�
	virtual void SetupPlayerInputComponent(UInputComponent* InputComp) override;


public: /* Callback */
	// ���픭��
	UFUNCTION()
	void OnUseWeapon(const FInputActionValue& Value);

	// �A�V�X�g����
	UFUNCTION()
	void OnUseAssist(const FInputActionValue& Value);

	// �_���[�W����
	UFUNCTION()
	void OnTakeDamage(float Damage);

public:
	// ���W�ݒ�
	void SetCurrentCoord(FVector2D Coord);
	FVector2D GetCurrentCoord() const;

	// ����𑕔�����
	void EquipWeapon(AWeaponActorBase* Weapon);
	// ���ݕ���𑕔�����
	bool IsEquippedWeapon() { return EquippedWeapon != nullptr; }

	// �Q�b�^
	UGridMovementComponent* GetGridMovementComponent() { return GridMovementComp; }


public: /* Input */
	// ���픭��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UseWeaponAction = nullptr;

	// �A�V�X�g����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UseAssistAction = nullptr;

	// �O���b�h�ړ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveGridAction = nullptr;

	// ��]���[�h
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* TurnTowardAction = nullptr;


public: /* Status */
	// HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 CurrentHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 MaxHP = 100;
	// �G�i�W�[
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 CurrentEnergy = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 MaxEnergy = 10;


public: /* ���� */
	// �}�Y���I�t�Z�b�g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	FVector MazzleOffset = FVector(0.f, 0.f, 50.f);

	// ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeaponActorBase* EquippedWeapon = nullptr;


public: /* �J�[�h */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UCardData* DefaultCardData = nullptr;


private: /* Component */
	// �O���b�h�ړ��R���|�[�l���g
	class UGridMovementComponent* GridMovementComp = nullptr;

private:
	// ���W
	FVector2D CurrentCoord = FVector2D::Zero();
};

