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

	// �z�u�E�X�|�[�����Ɏ�����AI�ɐ��䂳���悤�w��
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// ���ʕ��������킹��悤�ɉ�]�ƈʒu����
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComp->SetupAttachment(RootComponent);
	// �V���h�E�𗎂Ƃ��Ȃ�
	WidgetComp->SetCastShadow(false);          
	// �f�J�[�����󂯂Ȃ�
	WidgetComp->bReceivesDecals = false;       
	// �����蔻����s�v
	WidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); 

	// �O���b�h�ړ��R���|�[�l���g
	GridMovementComp = CreateDefaultSubobject<UGridMovementComponent>(TEXT("GridMovementComponent"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// �Q�[���I�����̃R�[���o�b�N�o�^
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (AMyGameMode* MyGM = Cast<AMyGameMode>(GM))
	{
		// �ړ��R���|�[�l���g�𖳌���
		MyGM->OnGameEnd.AddLambda([this, MyGM]() {
			if (auto* MovementComp = GetCharacterMovement())
			{
				MovementComp->DisableMovement();
			}

			if (AAIController* AIController = Cast<AAIController>(GetController()))
			{
				// ��]�𖳌���
				bUseControllerRotationYaw = false;

				// BT / MoveTo �����S��~
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

	// HP�o�[�Ɏ��g��n��
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

	// �A�N�V�����t�F�[�Y�ȊO�ł͎��Ԓ�~
	if (MyGameMode->GetCurrentButtlePhase() != EBattlePhase::Action)
	{
		this->CustomTimeDilation = 0.f;
		return;
	}

	this->CustomTimeDilation = 1.f;

	Super::Tick(DeltaTime);

	// HP�o�[�̍X�V
	UpdateHPBarWidget();

	// �����Ńv���C���[�̕����։�]
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
	// �_���[�W���󂯂�
	CurrentHP = FMath::Max(CurrentHP - TakeDamage, 0.f);

	if (CurrentHP <= 0)
	{
		// ���S������
		OnDead();

		// �j��
		Destroy();
	}
}

// ���S���̃R�[���o�b�N
void AEnemyBase::OnDead()
{
	// ���݂̍��W�̃O���b�h�Z����������폜
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

// HP�o�[�̍X�V
void AEnemyBase::UpdateHPBarWidget()
{
	if (WidgetComp == nullptr)
		return;

	// ��ɃJ���������ʂɂȂ�悤�ɉ�]������
	FRotator LookAtRotation = (FVector::XAxisVector * -1.f).Rotation();

	WidgetComp->SetWorldRotation(LookAtRotation);
}

// �v���C���[�̕���������
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

	// ��]�\��Ԃ�
	if (CanRotate() == false)
		return;

	// �v���C���[�Əc�E���E�΂߂̐���ɂ���ꍇ������]
	if (GridManager->IsPlayerSameLine(GridMovementComp->GetCurrentCoord()) == false)
		return;

	// �v���C���[�̎擾
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
		return;
	APawn* Pawn = PlayerController->GetPawn();
	if (Pawn == nullptr)
		return;

	// �v���C���[�ւ̕������擾
	FVector Direction = Pawn->GetActorLocation() - this->GetActorLocation();
	// Z������̉�]�����ł����̂Œ���
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