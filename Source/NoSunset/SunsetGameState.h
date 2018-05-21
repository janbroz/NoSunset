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
	
	void InitializeSpawners();

	UFUNCTION()
		void RespondToMinionKilled(class AActor* MinionKilled, class AController* EventInstigator, AActor* DamageCauser);
	UFUNCTION()
		void HandleWaveCleared();
	UFUNCTION()
		class AProjectile* GetUsableProjectile(TSubclassOf<class AProjectile> ProjectileClass);
	UFUNCTION()
		bool AddProjectileToPool(AProjectile* ProjectileToAdd);
	UFUNCTION()
		void InitializeGame();
	UFUNCTION()
		void LevelCompleted(bool bSuccessfully, APlayerController* Controller);
	UFUNCTION()
		void UpdatePlayersUIWave();
	UFUNCTION()
		void UpdatePlayersUIEnemies();


private:
	void SpawnNextWave();

public:
	// New wave logic
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		uint32 bWaveStarted : 1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 CurrentWave;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 EnemiesToSpawn;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 EnemiesSpawned;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 EnemiesAlive;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 EnemiesKilled;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		uint32 bWaveFullySpawned : 1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		TSubclassOf<class AMinion> CurrentMinionClass;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		uint32 bRoundIsOver : 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		int32 NumberOfWaves;	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		float TimeBetweenWaves;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		class AWaveSpawner* LevelWaveSpawner;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		class UGlobalEventHandler* EventHandler;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		class AMinionGoal* LevelGoalZone;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Minion information")
		class UProjectilePoolComponent* ProjectilePoolManager;

};
