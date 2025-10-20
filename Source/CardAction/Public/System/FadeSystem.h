// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <UI/FadeWidget.h>
#include "FadeSystem.generated.h"

/**
 * 
 */
UCLASS()
class CARDACTION_API UFadeSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void FadeOutAndOpenLevel(FName LevelName);
	void FadeIn(float FadeSec = 1.f);
	void FadeOut(float FadeSec = 1.f);

	// �t�F�[�h����
	bool IsFade();
	bool IsFadeIn();
	bool IsFadeOut();

	// �t�F�[�h�X�V
	void UpdateFade(float DeltaSec);

private:
	UPROPERTY();
	UFadeWidget* FadeWidget;

	// ���t���[���X�V�p�̃f���Q�[�g�n���h��
	FDelegateHandle TickHandle;
};
