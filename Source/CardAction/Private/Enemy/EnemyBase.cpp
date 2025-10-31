// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include <Kismet/GameplayStatics.h>
#include <System/MyGameMode.h>
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <AIController.h>
#include <Character/MyCharacter.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <UI/HUD/HPBar.h>
#include "Grid/GridManager.h"
#include "Enemy/EnemyManager.h"

AEnemyBase::AEnemyBase()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 42.f);

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

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		// ゲーム終了時のコールバック登録
		MyGM->OnGameEnd.AddLambda([this, MyGM]() {
			// 死んでいる場合は無視
			if (IsValid(this) == false)
				return;

			// 移動コンポーネントを無効化
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

		// アクションフェーズ開始時のコールバック登録
		MyGM->OnStartActionPhase.AddLambda([this, MyGM]() {
			// 死んでいる場合は無視
			if (IsValid(this) == false)
				return;

			// AIが止まっていたら再開
			auto* Contoller = GetController();
			if (Contoller == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Controller is nullptr"));
				return;
			}

			AAIController* AIController = Cast<AAIController>(Contoller);
			if (AIController)
			{
				if (AIController && AIController->BrainComponent)
				{
					AIController->BrainComponent->StartLogic();
				}
			}

			// Tick再開
			this->CustomTimeDilation = 1.f;
			});
	}

	// TargetActorにプレイヤーを登録
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValueAsObject("TargetActor", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		}
	}

	// HPバーの設定
	if (WidgetComp)
	{
		if (UHPBar* HPWidget = Cast<UHPBar>(WidgetComp->GetUserWidgetObject()))
		{
			// HP取得用の関数設定
			FOnGetMaxHP GetMaxHPFunc;
			GetMaxHPFunc.BindLambda([this]()
				{
					if (IsValid(this) == false)
						return 0;

					return MaxHP;
				});

			FOnGetCurrentHP GetCurrentHPFunc;
			GetCurrentHPFunc.BindLambda([this]()
				{
					if (IsValid(this) == false)
						return 0;

					return CurrentHP;
				});
			HPWidget->Setup(WidgetComp, GetMaxHPFunc, GetCurrentHPFunc);

			// エネミー用のレイアウトに変更
			HPWidget->ChangeLayout(EHPBarType::Enemy);
		}
	}

	// エネミーマネージャーに自身を登録
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->EnemyManager)
		{
			MyGM->EnemyManager->RegistEnemy(this);
		}
	}
}

void AEnemyBase::BeginDestroy()
{
	Super::BeginDestroy();

	// エネミーマネージャーから自身を解除
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->EnemyManager)
		{
			MyGM->EnemyManager->UnRegistEnemy(this);
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

	// 開始/アクション フェーズ以外では時間停止
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Entry && MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
	{
		this->CustomTimeDilation = 0.f;

		// AIも止める
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			if (AIController && AIController->BrainComponent)
			{
				// BrainComponent に対して BT 停止
				AIController->BrainComponent->StopLogic("ExternalStop");
			}
		}

		return;
	}

	Super::Tick(DeltaTime);

	// 死亡していたら自身を消す
	if (bIsDead)
	{
		Destroy();
	}

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
		OnBeforeDead();

		// 死亡アニメーション再生
		if (GetMesh() && GetMesh()->GetAnimInstance() && DeadAnimMontage)
		{
			auto* AnimInstance = GetMesh()->GetAnimInstance();
			AnimInstance->Montage_Play(DeadAnimMontage);
		
			// モンタージュが終了したら死亡フラグを立てる
			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &AEnemyBase::OnEndDeadMontage);
			AnimInstance->Montage_SetEndDelegate(EndDelegate, DeadAnimMontage);
		}
		// 削除
		else
		{
			SelfDestroy();
		}
	}
	// 死んでいない場合、ヒットモンタージュ再生
	else
	{
		// 死亡アニメーション再生
		if (GetMesh() && GetMesh()->GetAnimInstance() && HitAnimMontage)
		{
			auto* AnimInstance = GetMesh()->GetAnimInstance();
			AnimInstance->Montage_Play(HitAnimMontage);
		}
	}
}

// 死亡時のコールバック
void AEnemyBase::OnBeforeDead()
{
	// BTを停止
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (AIController->BrainComponent)
		{
			AIController->BrainComponent->StopLogic(TEXT("Dead"));
		}
	}

	OnEnemyDied.Broadcast(this);
}

void AEnemyBase::OnEndDeadMontage(UAnimMontage* Montage, bool bInterrupted)
{
	bIsDead = true;

	// アニメーション終了後は完全停止
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;

	// 削除
	SelfDestroy();
}

// 死亡モンタージュ再生中か
bool AEnemyBase::IsPlayingDeadMontage()
{
	if (GetMesh() == nullptr)
		return false;
	if (GetMesh()->GetAnimInstance() == nullptr)
		return false;

	return GetMesh()->GetAnimInstance()->Montage_IsPlaying(DeadAnimMontage);
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

// 自身の削除
void AEnemyBase::SelfDestroy()
{
	// 現在の座標のグリッドセルから情報を削除
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (MyGM->GridManager)
		{
			MyGM->GridManager->RemoveActorFromCell(this, GetCurrentCoord());
		}
	}

	Destroy();
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