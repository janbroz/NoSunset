// Fill out your copyright notice in the Description page of Project Settings.

#include "NoSunsetGameModeBase.h"
#include "Player/SunsetPawn.h"
#include "Player/SunsetPlayerController.h"

ANoSunsetGameModeBase::ANoSunsetGameModeBase()
{
	DefaultPawnClass = ASunsetPawn::StaticClass();
	PlayerControllerClass = ASunsetPlayerController::StaticClass();
}
