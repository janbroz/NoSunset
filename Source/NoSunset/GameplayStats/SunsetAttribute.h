// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SunsetAttribute.generated.h"

/**
 * 
 */



USTRUCT(Blueprintable)
struct FAttributeData
{
	GENERATED_BODY()

	FAttributeData()
	: BaseValue(0.f)
	, CurrentValue(0.f){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute information")
		float BaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute information")
		float CurrentValue;

};


UCLASS()
class NOSUNSET_API USunsetAttribute : public UObject
{
	GENERATED_BODY()
public:
	USunsetAttribute();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Actor attributes")
		FAttributeData Health;
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
