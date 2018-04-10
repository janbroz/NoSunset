// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SunsetAttribute.generated.h"

/**
 * 
 */

struct FEffectSpec;

USTRUCT(BlueprintType)
struct FAttributeData
{
	GENERATED_BODY()

	FAttributeData()
		: BaseValue(0.f)
		, CurrentValue(0.f)
	{}

	FAttributeData(float DefaultValue)
		: BaseValue(DefaultValue)
		, CurrentValue(DefaultValue)
	{}

	virtual ~FAttributeData()
	{}

	float GetCurrentValue() const;
	virtual void SetCurrentValue(float NewValue);

	float GetBaseValue() const;
	virtual void SetBaseValue(float NewValue);

	void ModifyCurrentValue(float NewValue);
	void ModifyBaseValue(float NewValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute information")
		float BaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute information")
		float CurrentValue;
};

USTRUCT(BlueprintType)
struct FAttribute
{
	GENERATED_BODY()

public:
	FAttribute()
		: Attribute(nullptr)
		, AttributeOwner(nullptr)
	{}

	FAttribute(UProperty* NewProperty);

	static bool IsAttributeDataProperty(const UProperty* Property);

	UProperty* GetUProperty() const { return Attribute; }

public:
	UPROPERTY(EditAnywhere, Category = SunsetAttribute)
		UProperty* Attribute;
	UPROPERTY(VisibleAnywhere, Category = SunsetAttribute)
		UStruct* AttributeOwner;
};



UCLASS()
class NOSUNSET_API USunsetAttribute : public UObject
{
	GENERATED_BODY()
public:
	USunsetAttribute();


public:
	FAttribute HealthAttribute();

	//void ApplyModifierEffect(USunsetEffect* EffectToApply);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actor attributes")
		FAttributeData Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor attributes")
		FAttributeData MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor attributes")
		FAttributeData Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor attributes")
		FAttributeData MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor attributes")
		FAttributeData AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor attributes")
		FAttributeData AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor attributes")
		FAttributeData AttackDamage;


	
};
