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


UENUM(BlueprintType)
enum class EEffectApplyMode : uint8
{
	Additive			UMETA(DisplayName="Additive"),
	Multiplicative		UMETA(DisplayName="Multiplicative")
};

USTRUCT(BlueprintType)
struct FActiveEffectsContainer
{
	GENERATED_BODY()
public:
	FActiveEffectsContainer();
	virtual ~FActiveEffectsContainer();

	bool AddEffect(USunsetEffect* NewEffect);


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
	
	UFUNCTION()
		void SetOwner(USunsetAbilityComponent* NewOwner);
	UFUNCTION()
		virtual void ApplyEffect();
	UFUNCTION()
		void ClearEffect();
	UFUNCTION()
		void ClearStack();

	void SayHey();
	float CalculateEffect();

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
	// Its an stackable effect?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint32 bCanStack : 1;
	// Stack count for the effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 StackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxStackAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StackDuration;
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
	// A Handle to remove a stack from our effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle StackHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USunsetAbilityComponent* Owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEffectApplyMode ApplyMode;

};
