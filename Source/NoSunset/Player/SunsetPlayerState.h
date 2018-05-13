// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DataStructures.h"
#include "SunsetPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API ASunsetPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ASunsetPlayerState();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void DamagePlayer(int32 Damage);
	UFUNCTION(BlueprintCallable)
		void ModifyGold(int32 Amount);

	UFUNCTION()
		void UpdateUICurrentWave(int32 NewWave);
	UFUNCTION()
		void UpdateUIEnemiesAlive(int32 Alive, int32 Spawned);

public:
	UPROPERTY()
		class ASunsetPlayerController* PlayerController;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 Gold;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 SpecialResource;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 CurrentLives;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 MaxLives;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		EHeroClass HeroClass;
	
};
