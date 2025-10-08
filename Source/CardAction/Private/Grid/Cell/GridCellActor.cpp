// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Cell/GridCellActor.h"
#include <Character/MyCharacter.h>
#include <Enemy/EnemyBase.h>

// Sets default values
AGridCellActor::AGridCellActor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // ���b�V������
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    EdgeLeftComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeLeft"));
    EdgeRightComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeRight"));
    EdgeTopComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeTop"));
    EdgeDownComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeDown"));
    if (MeshComp)
    {
        MeshComp->SetupAttachment(RootComponent);
        EdgeLeftComp->SetupAttachment(RootComponent);
        EdgeRightComp->SetupAttachment(RootComponent);
        EdgeTopComp->SetupAttachment(RootComponent);
        EdgeDownComp->SetupAttachment(RootComponent);
    }

    // �R���W��������
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    if (CollisionComp)
    {
        CollisionComp->SetupAttachment(MeshComp);
    }
}

void AGridCellActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (MeshComp)
    {
        // ���b�V�����\��
        if (CellData.GridCellType == EGridCellType::None)
        {
            //MeshComp->SetVisibility(false, true);
            CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }

    if (CollisionComp)
    {
        CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    }
}

// Called when the game starts or when spawned
void AGridCellActor::BeginPlay()
{
    Super::BeginPlay();

    //// ���I�}�e���A�����쐬
    //DefaultDynamicMaterial = UMaterialInstanceDynamic::Create(DefaultMaterial, this);
    //DamegeSignDynamicMaterial = UMaterialInstanceDynamic::Create(DamegeSignMaterial, this);
}

// Called every frame
void AGridCellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// �Z����̃A�N�^�[��ǉ�
void AGridCellActor::AddActorOnCell(AActor* Actor)
{
    CellData.Objects.Add(Actor);
}

// �Z���ォ��A�N�^�[������
void AGridCellActor::RemoveActorFromCell(AActor* Actor)
{
    CellData.Objects.Remove(Actor);
}

// �Z����ɃA�N�^�[���݂��邩
bool AGridCellActor::IsExistActorOnCell()
{
    return CellData.Objects.IsEmpty() == false;
}

void AGridCellActor::ChangeDamageSignMaterial()
{
    if (MeshComp && CellData.DamegeSignMaterial)
    {
        MeshComp->SetMaterial(0, CellData.DamegeSignMaterial);
    }
}

void AGridCellActor::ChangeDefaultMaterial()
{
    if (MeshComp)
    {
        if (CellData.GridCellType == EGridCellType::Normal && CellData.DefaultMaterial)
        {
            MeshComp->SetMaterial(0, CellData.DefaultMaterial);
        }
        // ���b�V�����\��
        if (CellData.GridCellType == EGridCellType::None)
        {
            MeshComp->SetVisibility(false, true);
            CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }
}

// �Z����̃A�N�^�[�Ƀ_���[�W����
void AGridCellActor::ExecuteAttackToActorOnCell(AActor* AttackedActor, float Damage)
{
    if (AttackedActor == nullptr)
        return;

    // �v���C���[����̍U�����ǂ���
    bool bFromPlayer = Cast<AWeaponActorBase>(AttackedActor) != nullptr;

    // �Z����̃A�N�^�[����������ꍇ�͑S�ĂɃ_���[�W����
    for (AActor* Actor : CellData.Objects)
    {
        // �G�Ƀ_���[�W
        if (bFromPlayer)
        {
            if (AEnemyBase* Enemy = Cast<AEnemyBase>(Actor))
            {
                Enemy->OnTakeDamage(Damage);
            }
        }
        // �v���C���[�Ƀ_���[�W
        else
        {
            if (AMyCharacter* Player = Cast<AMyCharacter>(Actor))
            {
                Player->OnTakeDamage(Damage);
            }
        }
    }
}

// �Z����ɓG�����݂��邩
bool AGridCellActor::IsExistEnemyOnCell()
{
    for (AActor* Actor : CellData.Objects)
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
        if (Enemy)
        {
            return true;
        }
    }

    return false;
}

// �U���\���̒ǉ�
void AGridCellActor::AddAttackSign()
{
    // ���Ƃ��ƍU���\����\�����Ă��Ȃ���
    bool bWasNoSign = AttackSignCount == 0;

    AttackSignCount++;

    // ���Ƃ��ƍU���\����\�����Ă��Ȃ�������A�U���\���p�̃}�e���A���ɕύX
    if (bWasNoSign)
    {
        ChangeDamageSignMaterial();
    }
}

// �U���\���̏���
void AGridCellActor::RemoveAttackSign()
{
    AttackSignCount = FMath::Max(0, AttackSignCount - 1);

    // �������U���\���J�E���^�[���Ȃ�������A�f�t�H���g�̃��b�V���ɖ߂�
    if (AttackSignCount == 0)
    {
        ChangeDefaultMaterial();
    }
}

