// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/Cell/GridCellActor.h"
#include "Grid/GridData.h"
#include <Enemy/EnemyBase.h>
#include "GridManager.generated.h"

UCLASS()
class CARDACTION_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridManager();

protected: /* UObject */
	virtual void BeginPlay() override;

public:	/* AActor */
	virtual void Tick(float DeltaTime) override;
	

public: /* ���� */
	// �O���b�h����
	void GenerateGrid(UGridData* GridData);
	// �G�l�~�[���O���b�h��ɃX�|�[��
	void SpawnEnemies();
	// �v���C���[���X�|�[�������郏�[���h���W�擾
	FVector GetPlayerSpawnPosition();

public: /* �Z���֘A���� */
	// �Z����ɃA�N�^�[��o�^
	void AddActorOnCell(AActor* Actor, FVector2D Coord);
	// �Z���ォ��A�N�^�[������
	void RemoveActorFromGrid(AActor* Actor, FVector2D Coord);

	// �Z����̃A�N�^�[�Ƀ_���[�W����
	void ExecuteAttackToGridCell(AActor* AttackedActor, float Damage, FVector2D Coord);

	// �Z����̃A�N�^�[���X�V
	void RefleshActorInfoOnCell(AActor* MoveActor, FVector2D FromCoord, FVector2D ToCoord);

public: /* �G */
	// �U���\����ǉ�
	void AddAttackSign(FVector2D Coord);
	// �U���\��������
	void RemoveAttackSign(FVector2D Coord);

	// �O���b�h��ɓG�����݂��邩
	bool IsExistEnemyOnGrid();

public: /* Util */
	// �O���b�h���W �� ���[���h���W�ɕϊ�
	FVector ConvertToWorldPosition(FVector2D Coord);
	// ���[���h���W �� �O���b�h���W�ɕϊ�
	FVector2D ConvertToGridCoord(FVector Position);

	// ��̍��W�� �c�E���E�΂� �̂����ꂩ�̐���ɂ��邩
	bool IsSameLine(FVector2D Coord1, FVector2D Coord2);
	// �v���C���[�Ǝw����W��������ɂ��邩
	bool IsPlayerSameLine(FVector2D Coord);
	// �A�N�Z�X�\�ȃO���b�h�Z����
	bool IsAccessableGridCell(FVector CheckPosition);

	// �O���b�h�Z�����擾
	AGridCellActor* GetGridCellActor(FVector2D Coord);
	AGridCellActor* GetGridCellActor(FVector Position);

	// �O���b�h�T�C�Y�̎擾
	FVector2D GetGridSize();

private:
	// �O���b�h���W�͈͊O�`�F�b�N
	bool IsInGrid(FVector2D Coord);


public:
	// ��������O���b�h�f�[�^
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UGridData* GenerateGridData = nullptr;

	// �X�|�[��������G�l�~�[���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<AEnemyBase>> SpawnEnemyArray;

private:
	// �O���b�h���
	TArray<TArray<AGridCellActor*>> Grid;
};
