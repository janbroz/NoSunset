// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, Category = UITalking)
		void ToggleBuildOptions(bool bBuilding);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = UITalking)
		void InitializeBuildableTowers();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = UITalking)
		void UpdatePlayerResources();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = UITalking)
		void ShowTowerInformation(class ATower* Tower);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = UITalking)
		void UpdateResourcesPanel();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = UITalking)
		void UpdateCurrentWave(int32 Number);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = UITalking)
		void UpdateEnemiesAlive(int32 Alive, int32 Spawned);

};
