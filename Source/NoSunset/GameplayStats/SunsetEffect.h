// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayStats/SunsetAttribute.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "SunsetEffect.generated.h"

/**
 * 
 */
class USunsetAbilityComponent;
class USunsetEffect;
struct FActiveEffectsContainer;


USTRUCT(BlueprintType)
struct FActiveEffectsContainer
{
	GENERATED_BODY()
public:
	FActiveEffectsContainer();
	virtual ~FActiveEffectsContainer();

	void AddEffect(USunsetEffect* NewEffect);


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 NumberOfEffects;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USunsetAbilityComponent* OwnerAbilityComponent;
	UPROPERTY(VisibleAnywhere)
		TArray<USunsetEffect*> AppliedEffects;
};


UCLASS(Blueprintable)
class NOSUNSET_API USunsetEffect : public UObject
{
	GENERATED_BODY()
public:
	USunsetEffect();	
	

	void SetOwner(USunsetAbilityComponent* NewOwner);
	virtual void ApplyEffect();
	void ClearEffect();

	void SayHey();
public:

	// What attribute is the Effect touching
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAttribute Attribute;
	// How much is it going to change (- or + float)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EffectValue;
	// Is this effect repeating?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint32 bIsPeriodic : 1;
	// Each x seconds repeat this effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Period;
	// How long should i apply the effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration;
	// The timer manager to destroy this bleeding effect.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle DurationHandle;
	// The timer manager to apply the effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle PeriodHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USunsetAbilityComponent* Owner;


};
