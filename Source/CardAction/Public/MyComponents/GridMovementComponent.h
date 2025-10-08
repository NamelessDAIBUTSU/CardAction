// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDACTION_API UGridMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridMovementComponent();

protected: /* UObject */
	virtual void BeginPlay() override;

public:	/* UActorComponent */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void MoveToDirection(FVector Direction);
	
	// �O���b�h�ړ�
	UFUNCTION()
	void OnMoveToDirection(const FInputActionValue& Value);

	// �ړ������L���b�V���̍폜
	UFUNCTION()
	void OnResetDirectionCache(const FInputActionValue& Value);

	// ��]�̂݃��[�h�̕ύX
	UFUNCTION()
	void OnChangeTurnMode(const FInputActionValue& Value);

	// ���W
	FVector2D GetCurrentCoord() const { return CurrentCoord; }
	void SetCoord(FVector2D Coord) { CurrentCoord = Coord; }


private:
	// �O���b�h�ړ����I��������
	bool IsFinishGridMove();

public:
	// 1�ړ��̃O���b�h�P��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float GridUnit = 200.f;

private:
	// ��]�����̃��[�h��
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	bool bIsTurningMode = false;

	// �ړ�����
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	bool bIsMoving = false;

	// �ړ������̃L���b�V��
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector DirectionCache = FVector::Zero();

	// �O���b�h�ړ��p�̈ړ���
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector MoveGridVector = FVector::Zero();
	// �O���b�h�ړ��̈ړ���ʒu
	UPROPERTY(VisibleAnywhere, Category = "GridMove")
	FVector TargetLocation = FVector::Zero();

	// ���݂̍��W
	FVector2D CurrentCoord = FVector2D::Zero();
};
