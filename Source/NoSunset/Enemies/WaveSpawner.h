// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.generated.h"

UCLASS()
class NOSUNSET_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitializeSpawner();
	void SpawnCurrentWave();



public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Placement information", Meta = (MakeEditWidget = true))
		FVector SpawingPoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level spawning information")
		TArray<TSubclassOf<class AMinion>> MinionClasses;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level spawning information")
		int32 EnemiesToSpawn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level spawning information")
		int32 EnemiesSpawned;
	
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "World information", Meta = (AllowPrivateAccess = true))
		class ASunsetGameState* WorldState;

};
