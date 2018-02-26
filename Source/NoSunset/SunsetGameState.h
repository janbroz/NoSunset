// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SunsetGameState.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API ASunsetGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ASunsetGameState();
	
	// Level Starts. Ask if there is a wave spawner, then say holi!
	virtual void BeginPlay() override;
	

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		uint32 bWaveStarted : 1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 NumberOfWaves;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 CurrentWave;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		float TimeBetweenWaves;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		class AWaveSpawner* LevelWaveSpawner;


};
