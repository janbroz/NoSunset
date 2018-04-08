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
struct FActiveEffect;
struct FEffectSpec;
struct FActiveEffectsContainer;


USTRUCT()
struct FActiveEffectHandle
{
	GENERATED_BODY()
public:
	FActiveEffectHandle()
	: Handle(0)
	{}

	FActiveEffectHandle(int32 InHandle)
		: Handle(InHandle)
	{}

	bool IsValid() const { return Handle != 0; }

	static FActiveEffectHandle GenerateNewHandle(USunsetAbilityComponent* OwningComp);

	USunsetAbilityComponent* GetOwningAbilitySystem();

	bool operator==(const FActiveEffectHandle& Other) const { return Handle == Other.Handle; }
	bool operator!=(const FActiveEffectHandle& Other) const { return Handle != Other.Handle; }

private:
	UPROPERTY()
		int32 Handle;


};


USTRUCT(BlueprintType)
struct FEffectSpec
{
	GENERATED_BODY()
public:
	FEffectSpec();
	FEffectSpec(const USunsetEffect* InDef);

	void ApplyEffect();


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		const USunsetEffect* EffectDefinition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Duration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Period;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		const USunsetAbilityComponent* OwnerAbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FTimerHandle THandle;

};

USTRUCT()
struct FActiveEffect
{
	GENERATED_BODY()
public:
	FActiveEffect() {}

	FActiveEffect(const FActiveEffect& Other);

	FActiveEffect(FActiveEffect&& Other);
	FActiveEffect& operator=(FActiveEffect&& Other);
	FActiveEffect& operator=(const FActiveEffect& Other);


	UPROPERTY()
		FEffectSpec Spec;
	UPROPERTY()
		FActiveEffectHandle Handle;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

};



USTRUCT(BlueprintType)
struct FActiveEffectsContainer
{
	GENERATED_BODY()
public:
	FActiveEffectsContainer();
	virtual ~FActiveEffectsContainer();


	// Apply the effect
	FActiveEffect* ApplyEffectSpec(const FEffectSpec& Spec);


	void AddEffect(const FEffectSpec& NewEffect);


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float NumberOfEffects;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USunsetAbilityComponent* OwnerAbilityComponent;
	UPROPERTY(VisibleAnywhere)
		TArray<FActiveEffect> ActiveEffects;
	UPROPERTY(VisibleAnywhere)
		TArray<FEffectSpec> ActiveEffects_Def;


};

USTRUCT(BlueprintType)
struct FModifierInfo
{
	GENERATED_BODY();
public:
	FModifierInfo() {}

	UPROPERTY(EditDefaultsOnly, Category = Modifier)
		FAttribute Attribute;
	UPROPERTY(EditDefaultsOnly, Category = Modifier)
		float Magnitude;
};


UCLASS(Blueprintable)
class NOSUNSET_API USunsetEffect : public UObject
{
	GENERATED_BODY()
public:
	USunsetEffect();
	
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FModifierInfo> Modifiers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Period;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration;


};
