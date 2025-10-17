// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Cell/GridCellActor.h"
#include <Character/MyCharacter.h>
#include <Enemy/EnemyBase.h>

// Sets default values
AGridCellActor::AGridCellActor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // メッシュ生成
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

    // コリジョン生成
    AttackCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    if (AttackCollisionComp)
    {
        AttackCollisionComp->SetupAttachment(MeshComp);
        AttackCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        AttackCollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
        AttackCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
        AttackCollisionComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
    }
}

void AGridCellActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AGridCellActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AGridCellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// セル上のアクターを追加
void AGridCellActor::AddActorOnCell(AActor* Actor)
{
    CellData.Objects.Add(Actor);
}

// セル上からアクターを除去
void AGridCellActor::RemoveActorFromCell(AActor* Actor)
{
    for (int i = CellData.Objects.Num() - 1; i >= 0; --i)
    {
        if (CellData.Objects[i] == Actor)
        {
            CellData.Objects.RemoveAt(i);
        }
    }
}

// セル上にアクター存在するか
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
        // メッシュを非表示
        if (CellData.GridCellType == EGridCellType::None)
        {
            MeshComp->SetVisibility(false, true);
        }
    }
}

// セル上のアクターにダメージ処理
void AGridCellActor::ExecuteAttackToActorOnCell(AActor* AttackedActor, float Damage)
{
    if (AttackedActor == nullptr)
        return;

    // プレイヤーからの攻撃かどうか
    bool bFromPlayer = Cast<AWeaponActorBase>(AttackedActor) != nullptr;

    // セル上のアクターが複数いる場合は全てにダメージ処理
    for (int i = CellData.Objects.Num() - 1; 0 <= i ; --i)
    {
        // 敵にダメージ
        if (bFromPlayer)
        {
            if (AEnemyBase* Enemy = Cast<AEnemyBase>(CellData.Objects[i]))
            {
                Enemy->OnTakeDamage(Damage);
            }
        }
        // プレイヤーにダメージ
        else
        {
            if (AMyCharacter* Player = Cast<AMyCharacter>(CellData.Objects[i]))
            {
                Player->OnTakeDamage(Damage);
            }
        }
    }
}

// セル上に敵が存在するか
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

// セル上のエネミーを取得
AEnemyBase* AGridCellActor::GetEnemyOnCell()
{
    for (AActor* Actor : CellData.Objects)
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
        if (Enemy)
        {
            return Enemy;
        }
    }

    return nullptr;
}

// 攻撃予測の追加
void AGridCellActor::AddAttackSign()
{
    // もともと攻撃予測を表示していないか
    bool bWasNoSign = AttackSignCount == 0;

    AttackSignCount++;

    // もともと攻撃予測を表示していなかったら、攻撃予測用のマテリアルに変更
    if (bWasNoSign)
    {
        ChangeDamageSignMaterial();
    }
}

// 攻撃予測の除去
void AGridCellActor::RemoveAttackSign()
{
    AttackSignCount = FMath::Max(0, AttackSignCount - 1);

    // もしも攻撃予測カウンターがなかったら、デフォルトのメッシュに戻す
    if (AttackSignCount == 0)
    {
        ChangeDefaultMaterial();
    }
}

