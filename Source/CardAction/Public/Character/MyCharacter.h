// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputAction.h>
#include <Weapon/WeaponBase.h>
#include <Card/CardData.h>
#include "MyComponents/GridMovementComponent.h"
#include <Components/WidgetComponent.h>
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
	void OnUseCard(const FInputActionValue& Value);

	// �J�[�h�I��
	UFUNCTION()
	void OnSelectFirstCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnSelectSecondCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnSelectThirdCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnSelectFourthCard(const FInputActionValue& Value);
	UFUNCTION()
	void OnScrollSelectCard(const FInputActionValue& Value);

	// �_���[�W����
	UFUNCTION()
	void OnTakeDamage(float Damage);

public:
	// ���W�ݒ�
	void SetCurrentCoord(FVector2D Coord);
	FVector2D GetCurrentCoord() const;

	// �Q�b�^
	UGridMovementComponent* GetGridMovementComponent() { return GridMovementComp; }

	// ��D�ɃJ�[�h��ǉ�
	void AddToHandCards(UCardData* CardData);
	// ��D����J�[�h������
	void RemoveFromHandCards(UCardData* CardData);

private:
	// ��D�E�B�W�F�b�g�ɔ��f
	void RefleshHandCards();

public: /* Input */
	// �J�[�h����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* UseCardAction = nullptr;

	// ��D�̑I��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectFirstCardAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectSecondCardAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectThirdCardAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SelectFourthCardAction = nullptr;
	// ��D�̑I���i�z�C�[���X�N���[���j
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ScrollSelectCardAction = nullptr;

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


private:
	// ��D�J�[�h
	UPROPERTY(VisibleAnywhere, Category = "Card")
	TArray<UCardData*> HandCards;
	// ��D�̑I�𒆃C���f�b�N�X
	UPROPERTY(VisibleAnywhere, Category = "Card")
	int SelectHandCardsIndex = 0;

	// �O���b�h�ړ��R���|�[�l���g
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UGridMovementComponent* GridMovementComp = nullptr;
	// HP�o�[�p�R���|�[�l���g
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UWidgetComponent* WidgetComp = nullptr;
};

