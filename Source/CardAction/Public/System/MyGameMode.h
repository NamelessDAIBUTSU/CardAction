// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include <System/Phase/BattlePhaseDef.h>
#include <Card/InitDeckData.h>
#include <Card/CardBook.h>
#include "MyGameMode.generated.h"

class AGridManager;
class ADeckManager;
class AEnemyManager;
class UBattlePhaseBase;
class AMyCharacter;

UCLASS()
class CARDACTION_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

public:
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void ChangePhase(EBattlePhase NextPhase);
	EBattlePhase GetCurrentButtlePhase() const;

	ACardBook* GetCardBook() { return CardBook; }

public:
	UFUNCTION()
	void OnGameOver();

public:
	// ��������v���C���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<APawn> PlayerPawnClass;

	// �O���b�h�}�l�[�W���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TSubclassOf<AGridManager> GridManagerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	AGridManager* GridManager;

	// �f�b�L�}�l�[�W���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TSubclassOf<ADeckManager> DeckManagerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card")
	ADeckManager* DeckManager;

	// �G�l�~�[�}�l�[�W���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AEnemyManager> EnemyManagerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	AEnemyManager* EnemyManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UInitDeckData* InitDeckData = nullptr;

	// �Q�[���I�����ɔ��΂���f���Q�[�g
	DECLARE_MULTICAST_DELEGATE(FOnGameEnd);
	FOnGameEnd OnGameEnd;

	// �A�N�V�����t�F�[�Y�J�n���ɔ��΂���f���Q�[�g
	DECLARE_MULTICAST_DELEGATE(FOnStartActionPhase);
	FOnStartActionPhase OnStartActionPhase;

private:
	// ���݂̃t�F�[�Y
	UPROPERTY(VisibleAnywhere, Category = "Phase")
	UBattlePhaseBase* CurrentBattlePhase = nullptr;

	// �v���C���[
	UPROPERTY(VisibleAnywhere, Category = "Player")
	AMyCharacter* Player = nullptr;

	// �v���C���[�R���g���[���[
	UPROPERTY(VisibleAnywhere, Category = "Player")
	APlayerController* PlayerController = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Card")
	ACardBook* CardBook;
};
