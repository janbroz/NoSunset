// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SunsetAbilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USunsetAbilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NOSUNSET_API ISunsetAbilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Ability interface")
		virtual class USunsetAbilityComponent* GetAbilityComponent() const = 0;
	
	
};
