// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataStructures.h"
#include "Projectile.generated.h"

UCLASS()
class NOSUNSET_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Enemy enters the tower range
	UFUNCTION()
		void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Enemy exits the tower range
	UFUNCTION()
		void OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EElementType DamageType;
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		class USphereComponent* ProjectileCollision;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		class UProjectileMovementComponent* ProjectileMovement;
};
