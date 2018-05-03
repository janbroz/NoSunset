// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataStructures.h"
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

private:
	class ASunsetGameState* GameState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Enemy enters the tower range
	UFUNCTION()
		void OnEnemyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Enemy exits the tower range
	UFUNCTION()
		void OnEnemyEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void AimTurret();
	UFUNCTION()
		void Attack();

	UFUNCTION()
		void SetTowerMode(ETowerMode Mode);

	void BeginTowerBuilding();
	void EndTowerBuilding();
	void Reload();
	void DrawRangeIndicator();
	void ToggleRangeIndicator(bool bShowRange);

	void UpdateBuildingWidget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		FName TowerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		TSoftObjectPtr<UTexture2D> IconAssetId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		EElementType AttackType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackInformation)
		TSubclassOf<class USunsetDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float SellMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerInformation)
		float BuildingTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower information")
		class UBoxComponent* PlacementBox;
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
		UDecalComponent* RangeDecalComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TowerInformation)
		class UWidgetComponent* TowerBuildingWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TowerInformation)
		class AMinion* Target;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TowerInformation)
		uint32 bCanAttack : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TowerInformation)
		uint32 bUsesProjectiles : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TowerInformation)
		uint32 bShowingRangeIndicator : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TowerInformation)
		uint32 bIsOverlappingWhileBuilding : 1;
	UPROPERTY(EditAnywhere, Category = TowerInformation)
		TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(VisibleAnywhere, Category = TowerInformation)
		FTimerHandle BuildTimerHandle;
	UPROPERTY(VisibleAnywhere, Category = TowerInformation)
		FTimerHandle AttackHandler;
	UPROPERTY(VisibleAnywhere, Category = TowerInformation)
		FTimerHandle BuildingCooldownHandle;
	
};
