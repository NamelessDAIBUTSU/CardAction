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
	virtual void OnAttack() PURE_VIRTUAL(OnAttack,);

	// ���L�҂̐ݒ�
	void SetOwner(class AMyCharacter* Player) { WeaponOwner = Player; }


public: /* Status */
	// �_���[�W
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int Damage = 0;

	// �N�[���_�E��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float CoolTime = 0.f;

	// ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float LimitSec = 0.f;

public: /* Component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshComp = nullptr;

protected:
	UPROPERTY(VisibleAnywhere)
	AMyCharacter* WeaponOwner = nullptr;
};
