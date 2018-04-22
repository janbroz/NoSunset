// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayStats/SunsetEffect.h"
#include "HealthReductionEffect.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API UHealthReductionEffect : public USunsetEffect
{
	GENERATED_BODY()
	
public:
	UHealthReductionEffect();

	virtual void ApplyEffect() override;
	
};
