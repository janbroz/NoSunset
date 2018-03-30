// Fill out your copyright notice in the Description page of Project Settings.

#include "NoSunsetGameModeBase.h"
#include "Player/SunsetPawn.h"
#include "Player/SunsetPlayerController.h"
#include "Player/SunsetPlayerState.h"
#include "SunsetGameState.h"
#include "SunsetGameInstance.h"

ANoSunsetGameModeBase::ANoSunsetGameModeBase()
{
	DefaultPawnClass = ASunsetPawn::StaticClass();
	PlayerControllerClass = ASunsetPlayerController::StaticClass();
	GameStateClass = ASunsetGameState::StaticClass();
	PlayerStateClass = ASunsetPlayerState::StaticClass();
	
}

void ANoSunsetGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	SetupWaveInformation();
}

void ANoSunsetGameModeBase::SetupWaveInformation()
{
	ASunsetGameState* SGameState = Cast<ASunsetGameState>(GameState);
	if (!SGameState) return;

	SGameState->CurrentWave = 1;
	SGameState->InitializeGame();
}


void ANoSunsetGameModeBase::SetDifficultyMode(EDifficultyMode DifficultyMode)
{

}
