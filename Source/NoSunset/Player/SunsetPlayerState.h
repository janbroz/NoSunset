// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
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
	

	UFUNCTION(BlueprintCallable)
		void DamagePlayer(int32 Damage);


public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 Gold;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 SpecialResource;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 CurrentLives;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 MaxLives;
	
};
