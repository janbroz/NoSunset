// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataStructures.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EElementType : uint8
{
	Fire		UMETA(DisplayName = "Fire"),
	Ice			UMETA(DisplayName = "Ice"),
	Earth		UMETA(DisplayName = "Earth"),
	Thunder		UMETA(DisplayName = "Thunder"),
	Holy		UMETA(DisplayName = "Holy"),
	Physical	UMETA(DisplayName = "Physical"),
	Magical		UMETA(DisplayName = "Magical")
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Naked		UMETA(DisplayName = "Naked"),
	Light		UMETA(DisplayName = "Light"),
	Medium		UMETA(DisplayName = "Medium"),
	Heavy		UMETA(DisplayName = "Heavy"),
	Chaos		UMETA(DisplayName = "Chaos")
};

inline uint8 GetTypeHash(const EElementType A) { return (uint8)A; }

USTRUCT()
struct NOSUNSET_API FSunsetDamageEvent : public FDamageEvent
{
	GENERATED_USTRUCT_BODY()

	FSunsetDamageEvent() {}
	FSunsetDamageEvent(TSubclassOf<class UDamageType> InDamageTypeClass) : FDamageEvent(InDamageTypeClass) {}
	FSunsetDamageEvent(EElementType Type) : TypeOfAttack(Type) {}

	UPROPERTY()
		EElementType TypeOfAttack;

	/** ID for this class. NOTE this must be unique for all damage events. */
	static const int32 ClassID = 3;
	virtual int32 GetTypeID() const override { return FSunsetDamageEvent::ClassID; };
};

/** Structure that defines a level up table entry */
USTRUCT(Blueprintable)
struct FDamageInteraction : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FDamageInteraction()
		: Physical(0)
		, Magical(0)
		, Ice(0)
		, Fire(0)
		, Earth(0)
		, Thunder(0)
		, Holy(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Physical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Magical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Ice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Fire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Earth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Thunder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Holy;
};


class NOSUNSET_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
