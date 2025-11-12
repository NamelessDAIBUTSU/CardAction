// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Cell/GridCellActor.h"
#include <Character/MyCharacter.h>
#include <Enemy/EnemyBase.h>
#include <Map/MapManager.h>
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Enemy/EnemyManager.h"

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

void AGridCellActor::BeginPlay()
{
    Super::BeginPlay();

    // デフォルトマテリアルを現在のマップ指定のものに変更
    UMapManager* MapManager = GetWorld()->GetGameInstance()->GetSubsystem<UMapManager>();
    if (MapManager == nullptr || MapManager->GetCurrentMap() == nullptr)
        return;
    auto* MapData = MapManager->GetCurrentMap()->GetMapData();
    UMaterialInterface* DefaultMaterial = MapData != nullptr ? MapData->DefaultMaterial : nullptr;
    CellData.DefaultMaterial = DefaultMaterial;

    // メッシュ設定
    if (CellData.GridCellType == EGridCellType::Normal)
    {
        MeshComp->SetMaterial(0, CellData.DefaultMaterial);
    }
    if (CellData.GridCellType == EGridCellType::None)
    {
        MeshComp->SetVisibility(false, true);
    }
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

    // 追加されたアクターの種類によって枠のマテリアルを変える
    if (AEnemyBase* Enemy = Cast<AEnemyBase>(Actor))
    {
        ChangeEdgeEnemyMaterial();
    }
    // プレイヤーにダメージ
    if (AMyCharacter* Player = Cast<AMyCharacter>(Actor))
    {
        ChangeEdgePlayerMaterial();
    }
}

// セル上からアクターを除去
void AGridCellActor::RemoveActorFromCell(AActor* Actor)
{
    for (int i = CellData.Objects.Num() - 1; i >= 0; --i)
    {
        if (CellData.Objects[i] == Actor)
        {
            CellData.Objects.RemoveAt(i);

            // 枠を通常のマテリアルに変更
            ChangeEdgeDefaultMaterial();
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

void AGridCellActor::ChangeEdgeMaterial(UMaterialInterface* Material)
{
    if (Material == nullptr)
        return;

    if (EdgeLeftComp)
    {
        EdgeLeftComp->SetMaterial(0, Material);
    }
    if (EdgeRightComp)
    {
        EdgeRightComp->SetMaterial(0, Material);
    }
    if (EdgeTopComp)
    {
        EdgeTopComp->SetMaterial(0, Material);
    }
    if (EdgeDownComp)
    {
        EdgeDownComp->SetMaterial(0, Material);
    }
}

void AGridCellActor::ChangeEdgeDefaultMaterial()
{
    ChangeEdgeMaterial(EdgeDefaultMaterial);
}

void AGridCellActor::ChangeEdgePlayerMaterial()
{
    ChangeEdgeMaterial(EdgePlayerMaterial);
}

void AGridCellActor::ChangeEdgeEnemyMaterial()
{
    ChangeEdgeMaterial(EdgeEnemyMaterial);
}

// セル上のアクターにダメージ処理
void AGridCellActor::ExecuteAttackToActorOnCell(AActor* AttackedActor, float Damage)
{
    if (AttackedActor == nullptr)
        return;

    AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGM == nullptr)
        return;

    AEnemyManager* EnemyManager = MyGM->EnemyManager;
    if (EnemyManager == nullptr)
        return;


    // プレイヤーからの攻撃かどうか
    bool bFromPlayer = Cast<AWeaponActorBase>(AttackedActor) != nullptr;

    // セル上のアクターが複数いる場合は全てにダメージ処理
    // 敵にダメージ
    if (bFromPlayer)
    {
        if (AEnemyBase* Enemy = EnemyManager->GetEnemy(CellData.GridCoord))
        {
            Enemy->OnTakeDamage(Damage);
        }
    }
    // プレイヤーにダメージ
    else
    {
        // プレイヤーの取得
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController == nullptr)
            return;

        if (AMyCharacter* Player = Cast<AMyCharacter>(PlayerController->GetPawn()))
        {
            if (Player->GetCurrentCoord() == CellData.GridCoord)
            {
                Player->OnTakeDamage(Damage);
            }
        }
    }
}

// セル上に敵が存在するか
bool AGridCellActor::IsExistEnemyOnCell()
{
    AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGM == nullptr)
        return false;

    AEnemyManager* EnemyManager = MyGM->EnemyManager;
    if (EnemyManager == nullptr)
        return false;

    return EnemyManager->GetEnemy(CellData.GridCoord) != nullptr;
}

// セル上にプレイヤーが存在するか
bool AGridCellActor::IsExistPlayerOnCell()
{
    // プレイヤーの取得
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController == nullptr)
        return false;

    AMyCharacter* Player = Cast<AMyCharacter>(PlayerController->GetPawn());
    if (Player == nullptr)
        return false;

    return CellData.GridCoord == Player->GetCurrentCoord();
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

