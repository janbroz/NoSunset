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

private:
	void GetANewTarget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Enemy enters the tower range
	UFUNCTION()
		void OnEnemyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Enemy exits the tower range
	UFUNCTION()
		void OnEnemyEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void AimTurret();
	

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TowerInformation)
		UStaticMeshComponent* TowerBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TowerInformation)
		UStaticMeshComponent* TowerHead;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TowerInformation)
		UStaticMeshComponent* TowerCanon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TowerInformation)
		USceneComponent* ProjectileSpawnLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TowerInformation)
		class USphereComponent* RangeSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TowerInformation)
		USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TowerInformation)
		class AMinion* Target;

};
