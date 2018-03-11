// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DataStructures.h"
#include "SunsetDamageType.generated.h"

/**
 * 
 */
UCLASS(const, Blueprintable, BlueprintType)
class NOSUNSET_API USunsetDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = DamageInformation)
		EElementType DamageType;

	
};
