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
	

public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 Gold;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = PlayerInformation)
		int32 SpecialResource;
	
};
