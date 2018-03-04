// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Minion.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMinionIsKilledSignature, class AActor*, KilledMinion, class AActor*, Instigator);

UCLASS()
class NOSUNSET_API AMinion : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Take on me! (Damage)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	// Destroy the minion and broadcast to the game state / game info.
	UFUNCTION(BlueprintCallable, Category = "Minion interaction")
		void KillMinion();

	
public:
	UPROPERTY(EditAnywhere, Category = "Event Manager")
		class UGlobalEventHandler* EventHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MinionInformation)
		float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MinionInformation)
		float MaxHealth;

};
