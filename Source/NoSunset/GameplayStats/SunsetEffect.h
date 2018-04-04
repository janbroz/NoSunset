// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayStats/SunsetAttribute.h"
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
struct FActiveEffect
{
	GENERATED_BODY()
public:
	FActiveEffect() {}



};

USTRUCT(BlueprintType)
struct FEffectSpec
{
	GENERATED_BODY()
public:
	FEffectSpec();
	FEffectSpec(const USunsetEffect* InDef);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		const USunsetEffect* EffectDefinition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Duration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Period;

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
	//UPROPERTY()
	//	FAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EffectValue;


};
