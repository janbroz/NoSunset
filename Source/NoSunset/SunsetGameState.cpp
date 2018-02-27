// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetGameState.h"
#include "Enemies/WaveSpawner.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GlobalEventHandler.h"

ASunsetGameState::ASunsetGameState()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));
	
}

void ASunsetGameState::BeginPlay()
{
	Super::BeginPlay();

	InitializeSpawners();
	EventHandler->OnMinionKilled.AddDynamic(this, &ASunsetGameState::RespondToMinionKilled);
}

void ASunsetGameState::InitializeSpawners()
{
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveSpawner::StaticClass(), Spawners);

	if (Spawners.Num() > 0)
	{
		for (auto WaveSpawner : Spawners)
		{
			AWaveSpawner* WSpawner = Cast<AWaveSpawner>(WaveSpawner);
			if (WSpawner)
			{
				LevelWaveSpawner = WSpawner;
				break;
			}
		}
	}

	if (LevelWaveSpawner)
	{
		LevelWaveSpawner->InitializeSpawner();
		LevelWaveSpawner->SpawnCurrentWave();
	}
}

void ASunsetGameState::RespondToMinionKilled(AActor* MinionKilled)
{
	UE_LOG(LogTemp, Warning, TEXT("Shit, someone got killed"));
}