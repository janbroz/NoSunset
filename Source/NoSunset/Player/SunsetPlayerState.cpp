// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Player/SunsetPlayerController.h"
#include "SunsetGameState.h"

ASunsetPlayerState::ASunsetPlayerState()
{
	//SetPlayerName(TEXT("Default Player"));
	Gold = 50;
	SpecialResource = 0;
	CurrentLives = 10;
	MaxLives = CurrentLives;
}


void ASunsetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASunsetPlayerState, Gold);
	DOREPLIFETIME(ASunsetPlayerState, SpecialResource);
	DOREPLIFETIME(ASunsetPlayerState, MaxLives);
	DOREPLIFETIME(ASunsetPlayerState, CurrentLives);
}

void ASunsetPlayerState::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ASunsetPlayerController>(GetOwner());
}

void ASunsetPlayerState::DamagePlayer(int32 Damage)
{
	CurrentLives -= Damage;
	CurrentLives = FMath::Clamp(CurrentLives, 0, MaxLives);

	if (PlayerController)
	{

	}

	if (CurrentLives <= 0)
	{
		auto Controller = Cast<APlayerController>(GetOwner());
		auto GameState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
		if (GameState && Controller)
		{
			GameState->bRoundIsOver = true;
			GameState->LevelCompleted(false, Controller);
			Controller->SetPause(true);
		}
	}
}

void ASunsetPlayerState::ModifyGold(int32 Amount)
{
	Gold += Amount; 

	if (PlayerController)
	{
		PlayerController->UpdateHUDResources();
	}
}

void ASunsetPlayerState::UpdateUICurrentWave(int32 NewWave)
{
	if (PlayerController)
	{
		PlayerController->UpdateHUDCurrentWave(NewWave);
	}
}

void ASunsetPlayerState::UpdateUIEnemiesAlive(int32 Alive, int32 Spawned)
{
	if (PlayerController)
	{
		PlayerController->UpdateHUDEnemiesAlive(Alive, Spawned);
	}
}