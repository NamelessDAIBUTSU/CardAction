// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include <System/Phase/BattlePhaseDef.h>
#include <Card/InitDeckData.h>
#include <Card/CardBook.h>
#include "MyGameMode.generated.h"

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
	TSubclassOf<class AGridManager> GridManagerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	class AGridManager* GridManager;

	// �f�b�L�}�l�[�W���[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TSubclassOf<class ADeckManager> DeckManagerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card")
	class ADeckManager* DeckManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UInitDeckData* InitDeckData = nullptr;

	// �Q�[���I�����ɔ��΂���f���Q�[�g
	DECLARE_MULTICAST_DELEGATE(FOnGameEnd);
	FOnGameEnd OnGameEnd;

private:
	// ���݂̃t�F�[�Y
	UPROPERTY(VisibleAnywhere, Category = "Phase")
	class UBattlePhaseBase* CurrentBattlePhase = nullptr;

	// �v���C���[
	UPROPERTY(VisibleAnywhere, Category = "Player")
	class AMyCharacter* Player = nullptr;

	// �v���C���[�R���g���[���[
	UPROPERTY(VisibleAnywhere, Category = "Player")
	APlayerController* PlayerController = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Card")
	ACardBook* CardBook;
};
