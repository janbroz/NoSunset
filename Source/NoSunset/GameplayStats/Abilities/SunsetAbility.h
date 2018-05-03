// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayStats/SunsetEffect.h"
#include "SunsetAbility.generated.h"

/**
 * 
 */
class USunsetAbility;
struct FAbilityContainer;


UENUM(BlueprintType)
enum class EAbilityType : uint8 
{
	Passive		UMETA(DisplayName= "Passive"),
	Active		UMETA(DisplayName= "Active")
};

USTRUCT(BlueprintType)
struct FAbilityContainer
{
	GENERATED_BODY()
public:
	FAbilityContainer();

	// 

public:
	TArray<USunsetAbility*> AbilityManager;



};


UCLASS(Blueprintable)
class NOSUNSET_API USunsetAbility : public UObject
{
	GENERATED_BODY()
public:
	USunsetAbility();
	
	UFUNCTION()
		void ApplyEffect();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AbilityName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAbilityType EffectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class USunsetEffect> EffectClass;
	
};
