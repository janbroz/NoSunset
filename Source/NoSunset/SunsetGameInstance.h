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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minion information")
		UDataTable* TowersTable;

};
