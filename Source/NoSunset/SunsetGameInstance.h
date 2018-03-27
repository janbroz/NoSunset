// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "DataStructures.h"
#include "SunsetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API USunsetGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USunsetGameInstance();

	virtual void Init() override;
	
	float GetArmorContribution(EElementType AttackType, EArmorType ArmorType);
	FString GetAttackName(EArmorType ArmorType);

	UFUNCTION(BlueprintCallable, Category=TowersInformation)
		TSoftClassPtr<class ATower> GetTowerSoftPtr(int32 Index, EHeroClass HeroClass);
	UFUNCTION(BlueprintCallable, Category = TowersInformation)
		FString GetTowerReference(int32 Index, EHeroClass HeroClass);
	UFUNCTION(BlueprintCallable, Category = TowersInformation)
		UClass* GetTowerClass(int32 Index, EHeroClass HeroClass);
	UFUNCTION(BlueprintCallable, Category = TowersInformation)
		int32 GetTowerNumber();
	UFUNCTION(BlueprintCallable, Category = GameInformation)
		void SetGameDifficulty(EDifficultyMode Difficulty);
	UFUNCTION(BlueprintCallable, Category = GameInformation)
		void GetCurrentWaveInformation(int32 WaveIndex, struct FWaveInformation& WaveInformation);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minion information")
		UDataTable* TowersTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minion information")
		UDataTable* BuildingsTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=WaveInformation)
		UDataTable* WaveInfoTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GameInformation)
		EDifficultyMode GameDifficulty;

};
