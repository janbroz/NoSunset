// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EElementType : uint8
{
	Fire		UMETA(DisplayName = "Fire"),
	Water		UMETA(DisplayName = "Water"),
	Earth		UMETA(DisplayName = "Earth"),
	Thunder		UMETA(DisplayName = "Thunder"),
	Holy		UMETA(DisplayName = "Holy"),
	Physical	UMETA(DisplayName = "Physical")
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Light		UMETA(DisplayName = "Light"),
	Medium		UMETA(DisplayName = "Medium"),
	Heavy		UMETA(DisplayName = "Heavy"),
	Chaos		UMETA(DisplayName = "Chaos")
};

inline uint8 GetTypeHash(const EElementType A) { return (uint8)A; }

class NOSUNSET_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
