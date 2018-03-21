// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataStructures.h"
#include "ProjectilePoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOSUNSET_API UProjectilePoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectilePoolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<FString> GetAllProjectileNames();
	void SpawnProjectileClasses();
	
	UFUNCTION()
		class AProjectile* GetUsableProjectile(TSubclassOf<class AProjectile> ProjectileClass);
	UFUNCTION()
		bool AddProjectileToPool(AProjectile* ProjectileToAdd);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProjectilePoolInformation")
		TArray<FClassPoolArray> PoolOfProjectiles;
	
};
