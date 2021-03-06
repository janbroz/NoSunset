// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DataStructures.h"
#include "NoSunsetGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API ANoSunsetGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANoSunsetGameModeBase();
	
	virtual void BeginPlay() override;


private:
	void SetupWaveInformation();

public:
	void SetDifficultyMode(EDifficultyMode DifficultyMode);

};
