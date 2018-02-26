// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameModeBase.h"
#include "Player/MainMenuController.h"



AMenuGameModeBase::AMenuGameModeBase()
{
	PlayerControllerClass = AMainMenuController::StaticClass();
}