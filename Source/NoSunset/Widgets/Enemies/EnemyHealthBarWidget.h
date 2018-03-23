// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API UEnemyHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION()
		void UpdateHealth(float NewHealth);
	UFUNCTION()
		void SetupHealth(float CurrentHealth, float MaxHealth);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=HealthInformation)
		float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HealthInformation)
		float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HealthInformation)
		float PercentHealth = 1;

	
};
