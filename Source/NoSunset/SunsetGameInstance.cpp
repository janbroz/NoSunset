// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetGameInstance.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "DataStructures.h"
#include "Towers/Tower.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

USunsetGameInstance::USunsetGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TowerLookupTable_BP(TEXT("DataTable'/Game/GameplayData/Sunset-ArmorResilience.Sunset-ArmorResilience'"));
	if (TowerLookupTable_BP.Object)
	{
		TowersTable = TowerLookupTable_BP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> BuildingsLookupTable_BP(TEXT("DataTable'/Game/GameplayData/Buildings.Buildings'"));
	if (BuildingsLookupTable_BP.Object)
	{
		BuildingsTable = BuildingsLookupTable_BP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> WaveInformationLookupTable_BP(TEXT("DataTable'/Game/GameplayData/WaveInfo.WaveInfo'"));
	if (WaveInformationLookupTable_BP.Object)
	{
		WaveInfoTable = WaveInformationLookupTable_BP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> MinionStatsLookupTable_BP(TEXT("DataTable'/Game/GameplayData/Minion-stats.Minion-stats'"));
	if (MinionStatsLookupTable_BP.Object)
	{
		MinionStatsTable = MinionStatsLookupTable_BP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> WaveDetailsLookupTable_BP(TEXT("DataTable'/Game/GameplayData/Wave-detail.Wave-detail'"));
	if (WaveDetailsLookupTable_BP.Object)
	{
		WaveDetailsTable = WaveDetailsLookupTable_BP.Object;
	}

	//GameDifficulty = EDifficultyMode::Easy;
}

void USunsetGameInstance::Init()
{
	UGameInstance::Init();
}

float USunsetGameInstance::GetArmorContribution(EElementType AttackType, EArmorType ArmorType)
{
	//UE_LOG(LogTemp, Warning, TEXT("It calculated something"));
	float Multiplier = 1.f;
	FString AttackName = GetAttackName(ArmorType);
	FName ColName = FName(*AttackName);

	FDamageInteraction* RowLookup = TowersTable->FindRow<FDamageInteraction>(ColName, "", true);
	if (RowLookup)
	{
		switch (AttackType)
		{
		case EElementType::Fire:
			Multiplier = RowLookup->Fire;
			break;
		case EElementType::Ice:
			Multiplier = RowLookup->Ice;
			break;
		case EElementType::Earth:
			Multiplier = RowLookup->Earth;
			break;
		case EElementType::Thunder:
			Multiplier = RowLookup->Thunder;
			break;
		case EElementType::Holy:
			Multiplier = RowLookup->Holy;
			break;
		case EElementType::Physical:
			Multiplier = RowLookup->Physical;
			break;
		case EElementType::Magical:
			Multiplier = RowLookup->Magical;
			break;
		default:
			break;
		}
	}
	return Multiplier;
}

FString USunsetGameInstance::GetAttackName(EArmorType ArmorType)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EArmorType"), true);
	if (!EnumPtr) return FString("Invalid");
	return EnumPtr->GetNameStringByValue((uint8)ArmorType);
}

TSoftClassPtr<ATower> USunsetGameInstance::GetTowerSoftPtr(int32 Index, EHeroClass HeroClass)
{
	FString IndexString = FString::FromInt(Index);
	FName RowName = FName(*IndexString);
	FHeroTowers* RowLookup = BuildingsTable->FindRow<FHeroTowers>(RowName, "", true);
	if (RowLookup)
	{
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

FString USunsetGameInstance::GetTowerReference(int32 Index, EHeroClass HeroClass)
{
	FString IndexString = FString::FromInt(Index);
	FName RowName = FName(*IndexString);
	FHeroTowers* RowLookup = BuildingsTable->FindRow<FHeroTowers>(RowName, "", true);
	if (RowLookup)
	{
		UClass* TowerClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Game/Blueprints/Towers/TheTower.TheTower_C"));
		ATower* TmpTower = LoadObject<ATower>(NULL, TEXT("/Game/Blueprints/Towers/TheTower.TheTower_C"), NULL, LOAD_None, NULL);
		if (TowerClass)
		{
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not a valid asset"));
		}
		return RowLookup->Magician;
	}
	else
	{
		return "Invalid";
	}
}

UClass* USunsetGameInstance::GetTowerClass(int32 Index, EHeroClass HeroClass)
{
	FString IndexString = FString::FromInt(Index);
	FName RowName = FName(*IndexString);
	FHeroTowers* RowLookup = BuildingsTable->FindRow<FHeroTowers>(RowName, "", true);
	if (RowLookup)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Stuff is: %s"), *RowLookup->Magician);
		//FString Sts = "/Game/Blueprints/Towers/TheTower.TheTower_C";
		UClass* TowerClass = LoadObject<UClass>(NULL, *RowLookup->Magician, NULL, LOAD_None, NULL);
		if (TowerClass)
		{
			return TowerClass;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

int32 USunsetGameInstance::GetTowerNumber()
{
	TArray<FHeroTowers*> ArrayOfTowers;
	BuildingsTable->GetAllRows("", ArrayOfTowers);
	return ArrayOfTowers.Num();
}

void USunsetGameInstance::SetGameDifficulty(EDifficultyMode Difficulty)
{
	GameDifficulty = Difficulty;
}

void USunsetGameInstance::GetCurrentWaveInformation(int32 WaveIndex, struct FWaveInformation& WaveInformation)
{
	FName Index = FName(*FString::FromInt(WaveIndex));
	FWaveInformation* RowLookup = WaveInfoTable->FindRow<FWaveInformation>(Index, "", true);
	if (RowLookup)
	{
		WaveInformation = *RowLookup;
	}
}

FWaveDetail& USunsetGameInstance::GetCurrentWaveDetailsForUI(int32 WaveIndex)
{
	FString IndexAsString = FString::FromInt(WaveIndex);
	FWaveDetail* RowDetail = WaveDetailsTable->FindRow<FWaveDetail>(*IndexAsString, "");
	return *RowDetail;
}