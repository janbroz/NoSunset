// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetGameState.h"
#include "Enemies/WaveSpawner.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


ASunsetGameState::ASunsetGameState()
{
	

}

void ASunsetGameState::BeginPlay()
{
	Super::BeginPlay();

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