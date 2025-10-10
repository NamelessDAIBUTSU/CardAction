// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <AIController.h>
#include <Character/MyCharacter.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <UI/HUD/EnemyHPBar.h>

// Sets default values
AEnemyBase::AEnemyBase()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 42.f);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 配置・スポーン時に自動でAIに制御されるよう指定
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 正面方向を合わせるように回転と位置調整
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComp->SetupAttachment(RootComponent);
	// シャドウを落とさない
	WidgetComp->SetCastShadow(false);          
	// デカールも受けない
	WidgetComp->bReceivesDecals = false;       
	// 当たり判定も不要
	WidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); 

	// グリッド移動コンポーネント
	GridMovementComp = CreateDefaultSubobject<UGridMovementComponent>(TEXT("GridMovementComponent"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// ゲーム終了時のコールバック登録
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
	{
		// 移動コンポーネントを無効化
		MyGM->OnGameEnd.AddLambda([this, MyGM]() {
			if (auto* MovementComp = GetCharacterMovement())
			{
				MovementComp->DisableMovement();
			}

			if (AAIController* AIController = Cast<AAIController>(GetController()))
			{
				// 回転を無効化
				bUseControllerRotationYaw = false;

				// BT / MoveTo を完全停止
				AIController->StopMovement();
			}
			});


	}

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValueAsObject("TargetActor", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		}
	}

	// HPバーに自身を渡す
	if (WidgetComp)
	{
		if (UEnemyHPBar* HPWidget = Cast<UEnemyHPBar>(WidgetComp->GetUserWidgetObject()))
		{
			HPWidget->SetOwner(this);
		}
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameMode);
	if (MyGameMode == nullptr)
		return;

	// アクションフェーズ以外では時間停止
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
	{
		this->CustomTimeDilation = 0.f;
		return;
	}

	this->CustomTimeDilation = 1.f;

	Super::Tick(DeltaTime);

	// HPバーの更新
	UpdateHPBarWidget();

	// 自動でプレイヤーの方向へ回転
	if (bIsAutoLookAtPlayer)
	{
		LookAtPlayer();
	}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyBase::OnTakeDamage(int TakeDamage)
{
	// ダメージを受ける
	CurrentHP = FMath::Max(CurrentHP - TakeDamage, 0.f);

	if (CurrentHP <= 0)
	{
		// 死亡時処理
		OnDead();

		// 破棄
		Destroy();
	}
}

// 死亡時のコールバック
void AEnemyBase::OnDead()
{
	// 現在の座標のグリッドセルから情報を削除
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
	{
		if (MyGM->GridManager)
		{
			MyGM->GridManager->RemoveActorFromGrid(this, GetCurrentCoord());
		}
	}

	OnEnemyDied.Broadcast(this);
}

// HPバーの更新
void AEnemyBase::UpdateHPBarWidget()
{
	if (WidgetComp == nullptr)
		return;

	// 常にカメラが正面になるように回転させる
	FRotator LookAtRotation = (FVector::XAxisVector * -1.f).Rotation();

	WidgetComp->SetWorldRotation(LookAtRotation);
}

// プレイヤーの方向を向く
void AEnemyBase::LookAtPlayer()
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	AMyGameMode* MyGM = Cast<AMyGameMode>(GM);
	if (MyGM == nullptr)
		return;
	AGridManager* GridManager = MyGM->GridManager;
	if (GridManager == nullptr)
		return;
	if (GridMovementComp == nullptr)
		return;

	// 回転可能状態か
	if (CanRotate() == false)
		return;

	// プレイヤーと縦・横・斜めの線上にいる場合だけ回転
	if (GridManager->IsPlayerSameLine(GridMovementComp->GetCurrentCoord()) == false)
		return;

	// プレイヤーの取得
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
		return;
	APawn* Pawn = PlayerController->GetPawn();
	if (Pawn == nullptr)
		return;

	// プレイヤーへの方向を取得
	FVector Direction = Pawn->GetActorLocation() - this->GetActorLocation();
	// Z軸周りの回転だけでいいので調整
	FRotator Rotation = FRotator(0.f, Direction.Rotation().Yaw, 0.f);

	this->SetActorRotation(Rotation);
}


void AEnemyBase::SetCurrentCoord(FVector2D Coord)
{
	if (GridMovementComp)
	{
		GridMovementComp->SetCoord(Coord);
	}
}

FVector2D AEnemyBase::GetCurrentCoord() const
{
	if (GridMovementComp)
	{
		return GridMovementComp->GetCurrentCoord();
	}

	return FVector2D::Zero();
}