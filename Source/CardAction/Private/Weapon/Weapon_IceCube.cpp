// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon_IceCube.h"
#include <Grid/GridManager.h>
#include <System/MyGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "GameFramework/ProjectileMovementComponent.h"

AWeapon_IceCube::AWeapon_IceCube()
{
    PrimaryActorTick.bCanEverTick = true;

    // 移動コンポーネント生成
    ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Move Comp"));

    // 当たり判定コンポーネント生成
    BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Component"));
    if (BoxCollisionComp)
    {
        BoxCollisionComp->SetupAttachment(RootComponent);
        BoxCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        BoxCollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
        BoxCollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

        BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_IceCube::OnOverlap);
    }

    // 当たり判定コンポーネント生成
    SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
    if (SphereCollisionComp)
    {
        SphereCollisionComp->SetupAttachment(RootComponent);
        SphereCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        SphereCollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
        SphereCollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

        SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_IceCube::OnTurn);
    }
}

void AWeapon_IceCube::Tick(float DeltaSec)
{
	Super::Tick(DeltaSec);

    // 回転
    UpdateRotate(DeltaSec);

    // 移動
    UpdateMove(DeltaSec);

    // スケール
    UpdateScale(DeltaSec);

    // 消滅判定
    UpdateCheckDestroy();
}

void AWeapon_IceCube::BeginPlay()
{
	Super::BeginPlay();

    RotateSpeed = RotateDeg;

    MoveSpeed = MoveCell * GRID_CELL_UNIT;

    // 速度設定
    if (ProjectileMoveComp)
    {
        ProjectileMoveComp->InitialSpeed = MoveSpeed;
        CurrentDirection = GetActorForwardVector();
        ProjectileMoveComp->Velocity = CurrentDirection * ProjectileMoveComp->InitialSpeed;
        // 重力なし
        ProjectileMoveComp->ProjectileGravityScale = 0.f;
    }
}

// 初期化
void AWeapon_IceCube::Initialize()
{
    AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGM == nullptr)
        return;

    AGridManager* GridManager = MyGM->GridManager;
    if (GridManager == nullptr)
        return;

    // 初期位置をセルの真ん中に変更
    FVector CenterLocation = GridManager->ConvertToWorldPosition(SpawnCoord);
    SetActorLocation(CenterLocation);
}

// 接触時、ダメージ処理とアイスキューブのサイズを小さくする
void AWeapon_IceCube::OnOverlap(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor == nullptr)
        return;

    AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGM == nullptr)
        return;

    AGridManager* GridManager = MyGM->GridManager;
    if (GridManager == nullptr)
        return;

    // 発射位置のグリッドマスとの当たり判定は無視
    FCoord Coord = GridManager->ConvertToGridCoord(OtherActor->GetActorLocation());
    if (Coord == SpawnCoord)
        return;

    // セル以外とは接触してもスキップする
    AGridCellActor* Cell = Cast<AGridCellActor>(OtherActor);
    if (Cell == nullptr)
        return;

    // 敵がいるマスか先に取得しておく
    bool bIsExistEnemyOnGridCell = GridManager->IsExistEnemyOnCell(Coord);

    // 敵マスの場合
    if (bIsExistEnemyOnGridCell && OverlapActorCache != OtherActor)
    {
        // ダメージ処理
        GridManager->ExecuteAttackToCell(this, Damage, Coord);

        //// ヒットエフェクト再生
        //UGameplayStatics::SpawnEmitterAtLocation(
        //    GetWorld(),
        //    HitEffect,
        //    GetActorLocation(),
        //    FRotator::ZeroRotator,
        //    FVector(1.0f),
        //    true
        //);
        
        // スケールの減少
        FVector CurrentScale = GetActorScale();
        CurrentScale -= FVector(LostScale);
        SetActorScale3D(CurrentScale);

        // 移動速度の減少
        MoveSpeed = FMath::Max(MoveSpeed - DecreaseMoveSpeed, 0.f);

        // 回転量の増加
        RotateSpeed = RotateDegOnAttack;

        // 連続当たり判定回避用の当たったアクターキャッシュ
        OverlapActorCache = OtherActor;

        UE_LOG(LogTemp, Warning, TEXT("Overlap(%d, %d)"), Coord.X, Coord.Y);
    }
}

void AWeapon_IceCube::OnTurn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGM == nullptr)
        return;

    AGridManager* GridManager = MyGM->GridManager;
    if (GridManager == nullptr)
        return;

    // セル以外とは接触してもスキップする
    AGridCellActor* Cell = Cast<AGridCellActor>(OtherActor);
    if (Cell == nullptr)
        return;

    // 次のセルが空 or 現在のセルがグリッドの端か
    FCoord CurrentCoord = GridManager->ConvertToGridCoord(GetActorLocation());
    bool bNeedTurn = GridManager->IsNextCellAccessible(CurrentDirection, CurrentCoord) == false;


    // 方向転換が必要なセル上にいる場合
    if (bNeedTurn)
    {
        // セル中央より移動しすぎないように調整
        FVector CurrentLocation = GetActorLocation();
        FVector CenterLocation = GridManager->ConvertToWorldPosition(CurrentCoord);
        SetActorLocation(CenterLocation);

        // 方向転換先を決める
        int RandNum = FMath::RandRange(0, 1);
        if (RandNum == 0)
        {
            RandNum = -1;
        }
        if (FMath::IsNearlyZero(CurrentDirection.X) == false)
        {
            CurrentDirection = FVector(0.f, RandNum, 0.f);
        }
        else if (FMath::IsNearlyZero(CurrentDirection.Y) == false)
        {
            CurrentDirection = FVector(RandNum, 0.f, 0.f);
        }

        // 新しい方向が進行不可の場合、逆方向に変える
        if (GridManager->IsNextCellAccessible(CurrentDirection, CurrentCoord) == false)
        {
            CurrentDirection *= -1.f;
        }

        // 移動量の変更
        ProjectileMoveComp->Velocity = CurrentDirection * ProjectileMoveComp->InitialSpeed;
        UE_LOG(LogTemp, Warning, TEXT("CurrentDirection(%f, %f)"), CurrentDirection.X, CurrentDirection.Y);
    }
}

// 回転更新
void AWeapon_IceCube::UpdateRotate(float DeltaSec)
{
    if (MeshComp)
    {
        FRotator Rot = MeshComp->GetRelativeRotation();
        Rot.Yaw += RotateSpeed * DeltaSec;
        MeshComp->SetRelativeRotation(Rot);
    }

    // 回転量が増えている場合、元の回転量に戻る用に減少させていく
    if (RotateSpeed > RotateDeg)
    {
        RotateSpeed = FMath::Max(RotateSpeed - DecreaseDegSpeed, RotateDeg);
    }
}

// 移動更新
void AWeapon_IceCube::UpdateMove(float DeltaSec)
{
    AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
    if (MyGM == nullptr)
        return;

    AGridManager* GridManager = MyGM->GridManager;
    if (GridManager == nullptr)
        return;


    //// 次のセルが空 or 現在のセルがグリッドの端か
    //FCoord CurrentCoord = GridManager->ConvertToGridCoord(GetActorLocation());
    //bool bNeedTurn = GridManager->IsNextCellAccessible(CurrentDirection, CurrentCoord) == false;
    //
    //// 方向転換が必要なセル上にいる場合
    //if (bNeedTurn)
    //{
    //    // セル中央より移動しすぎないように調整
    //    FVector CurrentLocation = GetActorLocation();
    //    FVector CenterLocation = GridManager->ConvertToWorldPosition(CurrentCoord);
    //    if (FMath::IsNearlyZero(CurrentDirection.X) == false)
    //    {
    //        // 上方向
    //        if (CurrentDirection.X > 0)
    //        {
    //            CurrentLocation = FVector(FMath::Min(CurrentLocation.X, CenterLocation.X), CurrentLocation.Y, CurrentLocation.Z);
    //        }
    //        // 下方向
    //        else
    //        {
    //            CurrentLocation = FVector(FMath::Max(CurrentLocation.X, CenterLocation.X), CurrentLocation.Y, CurrentLocation.Z);
    //        }
    //    }
    //    if (FMath::IsNearlyZero(CurrentDirection.Y) == false)
    //    {
    //        // 右方向
    //        if (CurrentDirection.Y > 0)
    //        {
    //            CurrentLocation = FVector(CurrentLocation.X, FMath::Min(CurrentLocation.Y, CenterLocation.Y), CurrentLocation.Z);
    //        }
    //        // 左方向
    //        else
    //        {
    //            CurrentLocation = FVector(CurrentLocation.X, FMath::Max(CurrentLocation.Y, CenterLocation.Y), CurrentLocation.Z);
    //        }
    //    }
    //    SetActorLocation(CurrentLocation);

    //    // セルの真ん中に来たら方向転換先を決める
    //    if (CurrentLocation.X == CenterLocation.X || CurrentLocation.Y == CenterLocation.Y)
    //    {
    //        int RandNum = FMath::RandRange(0, 1);
    //        if (RandNum == 0)
    //        {
    //            RandNum = -1;
    //        }
    //        if (FMath::IsNearlyZero(CurrentDirection.X) == false)
    //        {
    //            CurrentDirection = FVector(0.f, RandNum, 0.f);
    //        }
    //        else if (FMath::IsNearlyZero(CurrentDirection.Y) == false)
    //        {
    //            CurrentDirection = FVector(RandNum, 0.f, 0.f);
    //        }

    //        // 新しい方向が進行不可の場合、逆方向に変える
    //        if (GridManager->IsNextCellAccessible(CurrentDirection, CurrentCoord) == false)
    //        {
    //            CurrentDirection *= -1.f;
    //        }

    //        // 移動量の変更
    //        ProjectileMoveComp->Velocity = CurrentDirection * ProjectileMoveComp->InitialSpeed;
    //    }
    //}

}

// スケール更新
void AWeapon_IceCube::UpdateScale(float DeltaSec)
{
    FVector CurrentScale = GetActorScale();
    CurrentScale -= FVector(DecreaseScaleSpeed);
    SetActorScale3D(CurrentScale);
}

// 現在のスケール, 移動スピードで消滅させるか判定
void AWeapon_IceCube::UpdateCheckDestroy()
{
    bool bDestroy = false;

    // スケール判定
    FVector CurrentScale =  GetActorScale();
    if (CurrentScale.X <= DestroyScale)
    {
        bDestroy = true;
    }

    // 移動スピード判定
    if(FMath::IsNearlyZero(MoveSpeed))
    {
        bDestroy = true;
    }

    if (bDestroy)
    {
        // 消滅
        Destroy();
    }
}
