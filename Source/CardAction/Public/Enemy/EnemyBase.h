// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/WidgetComponent.h>
#include "Delegates/DelegateCombinations.h"
#include <MyComponents/GridMovementComponent.h>
#include "EnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDead, AEnemyBase*, DeadEnemy);

UCLASS()
class CARDACTION_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: /* Callback */
	UFUNCTION()
	void OnTakeDamage(int TakeDamage);

	// ���S���̃R�[���o�b�N
	UFUNCTION()
	virtual void OnBeforeDead();

public:
	// ��]�\��
	virtual bool CanRotate() { return true; }

	// ���W
	void SetCurrentCoord(FVector2D Coord);
	FVector2D GetCurrentCoord() const;

	// �O���b�h�ړ��R���|�[�l���g
	UGridMovementComponent* GetGridMovementComponent() { return GridMovementComp; }

	// ���S�����^�[�W���I���㏈��
	void OnEndDeadMontage(UAnimMontage* Montage, bool bInterrupted);
	// ���񂾂�
	bool IsDead() const { return bIsDead; }
	// ���S�����^�[�W���Đ�����
	bool IsPlayingDeadMontage();

	// �J�n�������ł��Ă��邩
	bool IsReady() const { return bIsReady; }
	void SetIsReady(bool IsReady) { bIsReady = IsReady; }

private:
	// �v���C���[�̕���������
	void LookAtPlayer();

public: /* Info */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FString Description;

public: /* Status */
	// �_���[�W
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int Damage = 0;
	// �̗�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int CurrentHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int MaxHP = 100;

	// �����Ńv���C���[�̕�����������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsAutoLookAtPlayer = true;

public: /* UI */
	// �A�C�R���摜
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UTexture2D* IconTexture = nullptr;

public: /* Anim */
	// ���S�����^�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* DeadAnimMontage = nullptr;

public: /* Callback */
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnEnemyDead OnEnemyDied;

public: /* Component */
	// HP�o�[
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UWidgetComponent* WidgetComp = nullptr;


protected: /* Component */
	// �O���b�h�ړ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UGridMovementComponent* GridMovementComp = nullptr;

protected:
	// ���񂾂�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsDead = false;

	// �J�n�������ł�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	bool bIsReady = false;
};
