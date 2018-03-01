// Fill out your copyright notice in the Description page of Project Settings.

#include "NoSunsetGameModeBase.h"
#include "Player/SunsetPawn.h"
#include "Player/SunsetPlayerController.h"
#include "Player/SunsetPlayerState.h"
#include "SunsetGameState.h"


ANoSunsetGameModeBase::ANoSunsetGameModeBase()
{
	DefaultPawnClass = ASunsetPawn::StaticClass();
	PlayerControllerClass = ASunsetPlayerController::StaticClass();
	GameStateClass = ASunsetGameState::StaticClass();
	PlayerStateClass = ASunsetPlayerState::StaticClass();
}
