// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SunsetGameState.h"
#include "Enemies/Minion.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AWaveSpawner::AWaveSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveSpawner::InitializeSpawner()
{
	WorldState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
	if (WorldState)
	{
		UE_LOG(LogTemp, Warning, TEXT("This is the best of both worlds %d"), WorldState->CurrentWave);
	}

}

void AWaveSpawner::SpawnCurrentWave()
{
	WorldState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
	if (WorldState && EnemiesSpawned < EnemiesToSpawn)
	{
		auto CurrentWave = WorldState->CurrentWave;
		TSubclassOf<AMinion> WaveMinionClass = MinionClasses[WorldState->CurrentWave];
		if (MinionClasses.IsValidIndex(CurrentWave))
		{
			const FVector SpawnerLocation = GetActorLocation();
			const FRotator SpawnerRotation = GetActorRotation();

			/*for (auto i = 0; i < EnemiesToSpawn; ++i)
			{
				FActorSpawnParameters FASP;
				FASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				auto CurrentMinion = GetWorld()->SpawnActor<AMinion>(MinionClasses[CurrentWave], SpawnerLocation, SpawnerRotation, FASP);
				if (CurrentMinion)
				{
					UE_LOG(LogTemp, Warning, TEXT("yay"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("fuck"));
				}
			}*/
			FActorSpawnParameters FASP;
			FASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			auto CurrentMinion = GetWorld()->SpawnActor<AMinion>(MinionClasses[CurrentWave], SpawnerLocation, SpawnerRotation, FASP);
			if (CurrentMinion)
			{
				EnemiesSpawned++;
			}

			if (EnemiesSpawned < EnemiesToSpawn)
			{
				FTimerHandle UnusedHandle;
				GetWorldTimerManager().SetTimer(UnusedHandle, this, &AWaveSpawner::SpawnCurrentWave, 0.5f, false);
			}
		}
	}
}