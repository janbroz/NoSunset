// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetGameState.h"
#include "Enemies/WaveSpawner.h"
#include "Enemies/MinionGoal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GlobalEventHandler.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Player/SunsetPlayerState.h"
#include "Player/SunsetPlayerController.h"
#include "Enemies/Minion.h"

ASunsetGameState::ASunsetGameState()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));
	TimeBetweenWaves = 5.f;
}

void ASunsetGameState::BeginPlay()
{
	Super::BeginPlay();

	InitializeSpawners();
	EventHandler->OnMinionKilled.AddDynamic(this, &ASunsetGameState::RespondToMinionKilled);
	EventHandler->OnClearedWave.AddDynamic(this, &ASunsetGameState::HandleWaveCleared);
}

void ASunsetGameState::InitializeSpawners()
{
	TArray<AActor*> Spawners;
	TArray<AActor*> Goals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveSpawner::StaticClass(), Spawners);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMinionGoal::StaticClass(), Goals);
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
	if (Goals.Num() > 0)
	{
		for (auto LevelGoal : Goals)
		{
			AMinionGoal* LGoal = Cast<AMinionGoal>(LevelGoal);
			if (LGoal)
			{
				LevelGoalZone = LGoal;
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

void ASunsetGameState::RespondToMinionKilled(AActor* MinionKilled, class AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Shit, someone got killed"));
	ASunsetPlayerController* SPC = Cast<ASunsetPlayerController>(EventInstigator);
	if (!SPC) return;
	for(auto PlayerState : PlayerArray)
	{
		ASunsetPlayerState* SPState = Cast<ASunsetPlayerState>(PlayerState);
		if (SPState && SPState == SPC->PlayerState)
		{
			AMinion* Minion = Cast<AMinion>(MinionKilled);
			if (!Minion) return;
			SPState->ModifyGold(Minion->Bounty);
			break;
		}
	}
}

void ASunsetGameState::HandleWaveCleared()
{
	CurrentWave++;
	// Not so unused now, eh?
	FTimerHandle UnusedHandle;
	// Do level stuff for the event of a wave finished
	if (LevelWaveSpawner)
	{
		LevelWaveSpawner->SetNextWave();
	}
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ASunsetGameState::SpawnNextWave, TimeBetweenWaves, false);
}

void ASunsetGameState::SpawnNextWave()
{
	if (LevelWaveSpawner)
	{
		LevelWaveSpawner->SpawnCurrentWave();
	}
}