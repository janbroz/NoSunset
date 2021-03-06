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
#include "Towers/ProjectilePoolComponent.h"
#include "Engine/World.h"
#include "SunsetGameInstance.h"
#include "Player/SunsetPlayerState.h"

ASunsetGameState::ASunsetGameState()
{
	ProjectilePoolManager = CreateDefaultSubobject<UProjectilePoolComponent>(TEXT("ProjectilePool"));

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

void ASunsetGameState::InitializeGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Wave just ot started"));
	USunsetGameInstance* SGameInstance = Cast<USunsetGameInstance>(GetGameInstance());
	if (!SGameInstance) return;

	UE_LOG(LogTemp, Warning, TEXT("So far so good"));

	FWaveInformation WaveInformation;
	SGameInstance->GetCurrentWaveInformation(CurrentWave, WaveInformation);
	EnemiesSpawned = 0;
	switch (SGameInstance->GameDifficulty)
	{
	case EDifficultyMode::Easy :
		EnemiesToSpawn = WaveInformation.Easy;
		break;
	case EDifficultyMode::Medium:
		EnemiesToSpawn = WaveInformation.Medium;
		break;
	case EDifficultyMode::Hard:
		EnemiesToSpawn = WaveInformation.Hard;
		break;
	default:
		EnemiesToSpawn = 0;
		break;
	}

	CurrentMinionClass = LoadClass<AMinion>(NULL, *WaveInformation.MinionClass, NULL, LOAD_None, NULL);
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
	//UE_LOG(LogTemp, Warning, TEXT("Shit, someone got killed"));
	EnemiesKilled++;
	EnemiesAlive = FMath::Clamp(EnemiesAlive - 1, 0, EnemiesToSpawn);
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

	if (EnemiesAlive == 0 && bWaveFullySpawned)
	{
		HandleWaveCleared();
	}

	UpdatePlayersUIEnemies();
}

void ASunsetGameState::HandleWaveCleared()
{
	CurrentWave++;
	bWaveFullySpawned = false;
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ASunsetGameState::SpawnNextWave, TimeBetweenWaves, false);
	
	UpdatePlayersUIWave();
}

void ASunsetGameState::SpawnNextWave()
{
	EnemiesKilled = 0;
	USunsetGameInstance* SGameInstance = Cast<USunsetGameInstance>(GetGameInstance());
	if (!SGameInstance) return;

	FWaveInformation WaveInformation;
	SGameInstance->GetCurrentWaveInformation(CurrentWave, WaveInformation);
	EnemiesSpawned = 0;
	switch (SGameInstance->GameDifficulty)
	{
	case EDifficultyMode::Easy:
		EnemiesToSpawn = WaveInformation.Easy;
		break;
	case EDifficultyMode::Medium:
		EnemiesToSpawn = WaveInformation.Medium;
		break;
	case EDifficultyMode::Hard:
		EnemiesToSpawn = WaveInformation.Hard;
		break;
	default:
		EnemiesToSpawn = 0;
		break;
	}
	CurrentMinionClass = LoadClass<AMinion>(NULL, *WaveInformation.MinionClass, NULL, LOAD_None, NULL);

	if (LevelWaveSpawner )
	{
		LevelWaveSpawner->SpawnCurrentWave();
	}

	if (!CurrentMinionClass)
	{
		LevelCompleted(true, GetWorld()->GetFirstPlayerController());
	}

	UpdatePlayersUIEnemies();
}

void ASunsetGameState::LevelCompleted(bool bSuccessfuly, APlayerController* Controller)
{
	if (bSuccessfuly)
	{
		UE_LOG(LogTemp, Warning, TEXT("Yay, level is completed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You lost"));
	}
	ASunsetPlayerController* PC = Cast<ASunsetPlayerController>(Controller);
	if (!PC) return;
	PC->ShowLevelCompletedMenu();
}


AProjectile* ASunsetGameState::GetUsableProjectile(TSubclassOf<class AProjectile> ProjectileClass)
{
	return ProjectilePoolManager->GetUsableProjectile(ProjectileClass);
}

bool ASunsetGameState::AddProjectileToPool(AProjectile* ProjectileToAdd)
{
	return ProjectilePoolManager->AddProjectileToPool(ProjectileToAdd);
}

void ASunsetGameState::UpdatePlayersUIEnemies()
{
	for (auto Player : PlayerArray)
	{
		ASunsetPlayerState* TmpPlayer = Cast<ASunsetPlayerState>(Player);
		if (TmpPlayer)
		{
			TmpPlayer->UpdateUIEnemiesAlive(EnemiesKilled, EnemiesToSpawn);
		}
	}
}

void ASunsetGameState::UpdatePlayersUIWave()
{
	for (auto Player : PlayerArray)
	{
		ASunsetPlayerState* TmpPlayer = Cast<ASunsetPlayerState>(Player);
		if (TmpPlayer)
		{
			TmpPlayer->UpdateUICurrentWave(CurrentWave);
		}
	}
}