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

UENUM(BlueprintType)
enum class EHeroClass : uint8
{
	Magician	UMETA(DisplayName = "Magician"),
	TechMaster	UMETA(DisplayName = "TechMaster"),
	Fighter		UMETA(DisplayName = "Fighter")
};

UENUM(BlueprintType)
enum class ETowerMode : uint8
{
	Placing		UMETA(DisplayName = "Placing"),
	Building	UMETA(DisplayName = "Building"),
	Working		UMETA(DisplayName = "Working"),
	Upgrading	UMETA(DisplayName = "Upgrading")
};

UENUM(BlueprintType)
enum class EDifficultyMode : uint8
{
	Easy		UMETA(DisplayName = "Easy"),
	Medium		UMETA(DisplayName = "Medium"),
	Hard		UMETA(DisplayName = "Hard")
};

UENUM(BlueprintType)
enum class EBuildLocation : uint8
{
	Wrong		UMETA(DisplayName = "Wrong"),
	Right		UMETA(DisplayName = "Right"),
	Working		UMETA(DisplayName = "Working")
};

inline uint8 GetTypeHash(const EElementType A) { return (uint8)A; }
inline uint8 GetTypeHash(const EArmorType A) { return (uint8)A; }
inline uint8 GetTypeHash(const EHeroClass A) { return (uint8)A; }
inline uint8 GetTypeHash(const ETowerMode A) { return (uint8)A; }
inline uint8 GetTypeHash(const EDifficultyMode A) { return (uint8)A; }

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

USTRUCT(Blueprintable)
struct FHeroTowers : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FHeroTowers()
		: Magician("")
		, Techmaster("")
		, Fighter("")
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		FString Magician;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		FString Techmaster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		FString Fighter;
};

USTRUCT(Blueprintable)
struct FWaveInformation : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FWaveInformation()
	: Easy(1)
	, Medium(1)
	, Hard(1)
	, MinionClass("")
	, bIsBossWave(false)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		int32 Easy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		int32 Medium;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		int32 Hard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		FString MinionClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingTowers)
		bool bIsBossWave;
};

USTRUCT(Blueprintable)
struct FWaveDetail : public FTableRowBase
{
	GENERATED_BODY()
public:
	FWaveDetail() :
	  MinionName("")
	, Health(0)
	, Armor(0)
	, Speed(0)
	, Detail("")
	, MinionTexture(nullptr)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveDetail)
		FString MinionName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveDetail)
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveDetail)
		int32 Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveDetail)
		int32 Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveDetail)
		FString Detail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WaveDetail)
		UTexture2D* MinionTexture;
};


USTRUCT(Blueprintable)
struct FMinionStats : public FTableRowBase
{
	GENERATED_BODY()
public:
	FMinionStats()
	: HealthDefault(0.f)
	, MaxHealthDefault(0.f)
	, ArmorDefault(0.f)
	, MovementSpeedDefault(0.f)
	, AttackRangeDefault(0.f)
	, AttackSpeedDefault(0.f)
	, AttackDamageDefault(0.f)
	{}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionStats)
		float HealthDefault;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionStats)
		float MaxHealthDefault;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionStats)
		float ArmorDefault;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionStats)
		float MovementSpeedDefault;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionStats)
		float AttackRangeDefault;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionStats)
		float AttackSpeedDefault;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionStats)
		float AttackDamageDefault;
};


USTRUCT(BlueprintType)
struct FClassPoolArray
{
	GENERATED_BODY()
public:
	FClassPoolArray(){}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileInformation)
		TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileInformation)
		TArray<class AProjectile*> InstantiatedProjectiles;
};




class NOSUNSET_API DataStructures
{
public:
	DataStructures();
	~DataStructures();
};
