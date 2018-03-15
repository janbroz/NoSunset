// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SunsetGameState.h"
#include "Enemies/Minion.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "GlobalEventHandler.h"

// Sets default values
AWaveSpawner::AWaveSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));
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
		EventHandler = WorldState->EventHandler;
		if (EventHandler)
		{
			EventHandler->OnMinionKilled.AddDynamic(this, &AWaveSpawner::HandleMinionKilled);
		}
	}
}

void AWaveSpawner::SpawnCurrentWave()
{
	WorldState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
	if (WorldState && EnemiesSpawned < EnemiesToSpawn)
	{
		auto CurrentWave = WorldState->CurrentWave;
		//TSubclassOf<AMinion> WaveMinionClass = MinionClasses[WorldState->CurrentWave];
		if (MinionClasses.IsValidIndex(CurrentWave))
		{
			const FVector SpawnerLocation = GetActorLocation();
			const FRotator SpawnerRotation = GetActorRotation();

			FActorSpawnParameters FASP;
			FASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			auto CurrentMinion = GetWorld()->SpawnActor<AMinion>(MinionClasses[CurrentWave], SpawnerLocation, SpawnerRotation, FASP);
			if (CurrentMinion)
			{
				EnemiesSpawned++;
				EnemiesAlive++;

				if (EnemiesSpawned == EnemiesToSpawn)
				{
					bWaveFullySpawned = true;
				}
				else
				{
					bWaveFullySpawned = false;
				}
			}

			if (EnemiesSpawned < EnemiesToSpawn)
			{
				FTimerHandle UnusedHandle;
				GetWorldTimerManager().SetTimer(UnusedHandle, this, &AWaveSpawner::SpawnCurrentWave, 0.5f, false);
			}
		}
	}
}

void AWaveSpawner::HandleMinionKilled(AActor* MinionKilled, class AController* EventInstigator, AActor* DamageCauser)
{
	EnemiesAlive = FMath::Clamp(EnemiesAlive-1, 0, EnemiesToSpawn);

	if (EnemiesAlive == 0 && bWaveFullySpawned)
	{
		EventHandler->OnClearedWave.Broadcast();
	}
}

void AWaveSpawner::SetNextWave()
{
	UE_LOG(LogTemp, Warning, TEXT("Set the next wave stuff man"));
	EnemiesSpawned = 0;
	EnemiesAlive = 0;
}

TSubclassOf<class AMinion> AWaveSpawner::GetCurrentWaveClass(int32 CurrentWave)
{
	if (MinionClasses.IsValidIndex(CurrentWave))
	{
		return MinionClasses[CurrentWave];
	}
	else
	{
		return nullptr;
	}

}