// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class NOSUNSET_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float SellMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float BuildingTime;

};
