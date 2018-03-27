// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataStructures.h"

#include "WaveSpawner.generated.h"

UCLASS()
class NOSUNSET_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitializeSpawner();
	void SpawnCurrentWave();
	void SetNextWave();

	UFUNCTION()
		void HandleMinionKilled(class AActor* KilledMinion, class AController* EventInstigator, AActor* DamageCauser);
	UFUNCTION(BlueprintCallable)
		TSubclassOf<class AMinion> GetCurrentWaveClass(int32 CurrentWave);

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Placement information", Meta = (MakeEditWidget = true))
		FVector SpawingPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level spawning information")
		TArray<TSubclassOf<class AMinion>> MinionClasses;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level spawning information")
		int32 EnemiesToSpawn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level spawning information")
		int32 EnemiesSpawned;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level spawning information")
		int32 EnemiesAlive;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		class UGlobalEventHandler* EventHandler;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave information")
		uint32 bWaveFullySpawned : 1;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "World information", Meta = (AllowPrivateAccess = true))
		class ASunsetGameState* WorldState;
	


};
