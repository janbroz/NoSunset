// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SunsetGameState.h"
#include "SunsetGameInstance.h"
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
		//UE_LOG(LogTemp, Warning, TEXT("This is the best of both worlds %d"), WorldState->CurrentWave);
		EventHandler = WorldState->EventHandler;
		if (EventHandler)
		{
			EventHandler->OnMinionKilled.AddDynamic(this, &AWaveSpawner::HandleMinionKilled);
		}
	}
}

void AWaveSpawner::SpawnCurrentWave()
{
	//UE_LOG(LogTemp, Warning, TEXT("Got called to spawn stuff"));

	WorldState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
	USunsetGameInstance* GameInstance = Cast<USunsetGameInstance>(GetGameInstance());

	// New and better logic!
	if (!WorldState || !GameInstance) return;
	
	if (WorldState->bWaveFullySpawned)
	{
		// Tell the game state to setup the next wave

	}

	if (WorldState->EnemiesSpawned < WorldState->EnemiesToSpawn && WorldState->CurrentMinionClass)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actually spawning stuff"));
		// Spawn the stuff.
		const FVector SpawnerLocation = GetActorLocation();
		const FRotator SpawnerRotation = GetActorRotation();

		FActorSpawnParameters FASP;
		FASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		auto CurrentMinion = GetWorld()->SpawnActor<AMinion>(WorldState->CurrentMinionClass, SpawnerLocation, SpawnerRotation, FASP);
		if (CurrentMinion)
		{
			WorldState->EnemiesSpawned++;
			WorldState->EnemiesAlive++;

			if (WorldState->EnemiesSpawned == WorldState->EnemiesToSpawn)
			{
				WorldState->bWaveFullySpawned = true;
			}
		}
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AWaveSpawner::SpawnCurrentWave, 0.7f, false);
	}
}

void AWaveSpawner::HandleMinionKilled(AActor* MinionKilled, class AController* EventInstigator, AActor* DamageCauser)
{
	/*EnemiesAlive = FMath::Clamp(EnemiesAlive-1, 0, EnemiesToSpawn);
	auto Minion = Cast<AMinion>(MinionKilled);
	if (Minion && Minion->bIsBoss)
	{
		EnemiesToSpawn = 10;
	}

	if (EnemiesAlive == 0 && bWaveFullySpawned)
	{
		EventHandler->OnClearedWave.Broadcast();
	}*/
}

void AWaveSpawner::SetNextWave()
{
	//UE_LOG(LogTemp, Warning, TEXT("Set the next wave stuff man"));
	/*EnemiesSpawned = 0;
	EnemiesAlive = 0;*/
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