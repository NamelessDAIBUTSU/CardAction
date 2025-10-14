// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API AWeaponActorBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponActorBase();
	~AWeaponActorBase();

public:
	// �v���C���[�ɂ��U���A�N�V������
	virtual void OnAttack() {};

	// ���L�҂̐ݒ�
	void SetWeaponOwner(class AMyCharacter* Player) { WeaponOwner = Player; }


public: /* Status */
	// �_���[�W
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int Damage = 0;
	// �N�[���_�E��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float CoolTime = 0.f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshComp = nullptr;

	// �U�����ɍĐ�����v���C���[�̃����^�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* AttackMontage = nullptr;

protected:
	UPROPERTY(VisibleAnywhere)
	AMyCharacter* WeaponOwner = nullptr;
};
