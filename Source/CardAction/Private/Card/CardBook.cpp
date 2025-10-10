// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/CardBook.h"

// Sets default values
ACardBook::ACardBook()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	MaskWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("MaskWidgetComponent"));
	if (MaskWidgetComp)
	{
		MaskWidgetComp->SetupAttachment(RootComponent);
		// シャドウを落とさない
		MaskWidgetComp->SetCastShadow(false);
		// デカールも受けない
		MaskWidgetComp->bReceivesDecals = false;
		// 当たり判定も不要
		MaskWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void ACardBook::BeginPlay()
{
	Super::BeginPlay();
	// 初期位置
	SetActorLocation(FVector(-1255.f, 570.f, 463.f));
	SetActorRotation(FRotator(0.f, -88.f, -19.f));
	SetActorScale3D(FVector(9.52f, 9.52f, 9.52f));
}

// Called every frame
void ACardBook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

