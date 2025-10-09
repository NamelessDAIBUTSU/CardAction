// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyAttackBase.h"
#include <Components/SphereComponent.h>
#include <NiagaraSystem.h>
#include "PumpkinBomb.generated.h"

/// <summary>
/// �p���v�L���G�l�~�[������������A�v���C���[�Ɍ������ĕ�������ɔ��ł����e
/// </summary>
UCLASS()
class CARDACTION_API APumpkinBomb : public AEnemyAttackBase
{
	GENERATED_BODY()
	
public:
	APumpkinBomb();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION()
	void OnHitGridCell(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	// �ړ��ɕK�v�ȃp�����[�^�̐ݒ�
	void Setup(FVector Position);

public:
	// �����G�t�F�N�g
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	UParticleSystem* ExplosionParticle = nullptr;

public: /* �ړ� */
	// ���b�ŗ������邩
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float FallSec = 0.5f;
	// �������̍ō��_
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float ZPoint = 300.f;
	// �d�͉����x
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float Gravity = 980.f;

private:
	// �����蔻��
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* SphereComp = nullptr;

	// �ڕW�n�_
	UPROPERTY(VisibleAnywhere, Category = "Move")
	FVector TargetPosition = FVector::Zero();
	// �J�n�n�_
	UPROPERTY(VisibleAnywhere, Category = "Move")
	FVector StartPosition = FVector::Zero();
	// �����x
	UPROPERTY(VisibleAnywhere, Category = "Move")
	FVector InitialVelocity = FVector::Zero();

	// �o�ߎ���
	UPROPERTY(VisibleAnywhere, Category = "Move")
	float ElapsedSec = 0.f;
};
