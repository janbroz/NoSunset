// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Towers/Projectile.h"
#include "ExplosiveProjectile.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API AExplosiveProjectile : public AProjectile
{
	GENERATED_BODY()
public:
	AExplosiveProjectile();


public:
	UFUNCTION()
		virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	// Enemy exits the tower range
	UFUNCTION()
		virtual void OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	


public:
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		class USphereComponent* ExplosionRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile information")
		float ExplosionRadious;


};
