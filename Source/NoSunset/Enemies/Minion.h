// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataStructures.h"
#include "GameplayStats/SunsetAbilityInterface.h"
#include "GameplayStats/SunsetAbilityComponent.h"
#include "Minion.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMinionIsKilledSignature, class AActor*, KilledMinion, class AActor*, Instigator);

UCLASS()
class NOSUNSET_API AMinion : public ACharacter, public ISunsetAbilityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void UpdateDamageReduction();

public:	

	virtual USunsetAbilityComponent* GetAbilityComponent() const override { return AbilitySystem; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Take on me! (Damage)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	// Destroy the minion and broadcast to the game state / game info.
	UFUNCTION(BlueprintCallable, Category = "Minion interaction")
		void KillMinion(class AController* EventInstigator, AActor * DamageCauser);

	UFUNCTION()
		void UpdateHealthBarLocation();
	UFUNCTION()
		void ModifyHealth(float Amount);
	UFUNCTION()
		void SetupUIHealth();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class USunsetAbilityComponent* AbilitySystem;
	UPROPERTY(EditAnywhere, Category = "Event Manager")
		class UGlobalEventHandler* EventHandler;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MinionInformation)
		class UWidgetComponent* HealthBarComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionInformation)
		FName UnitName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionInformation)
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionInformation)
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionInformation)
		int32 Bounty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionInformation)
		EArmorType ArmorType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionInformation)
		float Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinionInformation)
		uint32 bIsBoss : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MinionInformation)
		uint32 bShowingHealthBar : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MinionInformation)
		float DamageReduction;

};
