// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Grid/Cell/GridCellData.h"
#include "GridCellActor.generated.h"

UCLASS()
class CARDACTION_API AGridCellActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridCellActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;

public:
	// �Z����̃A�N�^�[��ǉ�
	void AddActorOnCell(AActor* Actor);
	// �Z���ォ��A�N�^�[������
	void RemoveActorFromCell(AActor* Actor);

	// �Z����ɃA�N�^�[���݂��邩
	bool IsExistActorOnCell();

	// �}�e���A���ݒ�
	void ChangeDamageSignMaterial();
	void ChangeDefaultMaterial();

	// �Z����̃A�N�^�[�Ƀ_���[�W����
	void ExecuteAttackToActorOnCell(AActor* AttackedActor, float Damage);

	// �Z����ɓG�����݂��邩
	bool IsExistEnemyOnCell();

public: /* �U���\�� */
	// �U���\���̒ǉ�
	void AddAttackSign();
	// �U���\���̏���
	void RemoveAttackSign();

public:
	// �X�^�e�B�b�N���b�V��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;
	// �g�����b�V��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeLeftComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeRightComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeTopComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* EdgeDownComp;

	// �U���Ƃ̓����蔻��p�R���W����
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* AttackCollisionComp = nullptr;

	// ���̃Z�����ێ�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	FGridCellData CellData;

private:
	// �U���\���̃��N�G�X�g�J�E���^
	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int AttackSignCount = 0;
};
