// Fill out your copyright notice in the Description page of Project Settings.

#include "Minion.h"
#include "Enemies/MinionController.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "GlobalEventHandler.h"
#include "SunsetGameState.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SunsetDamageType.h"
#include "SunsetGameInstance.h"

// Sets default values
AMinion::AMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMinionController::StaticClass();
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));

	Health = 100.f;
	MaxHealth = Health;
	
}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDefaultController();

	ASunsetGameState* SunsetGameState = Cast<ASunsetGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (SunsetGameState)
	{
		EventHandler = SunsetGameState->EventHandler;
	}
	UpdateDamageReduction();
}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMinion::KillMinion()
{
	// Call either the wave spawner or the game state.

	//Minion_OnKilled.Broadcast(this, nullptr);
	EventHandler->OnMinionKilled.Broadcast(this);
	Destroy();
}

float AMinion::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float DamageCaused = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	const FSunsetDamageEvent* MyDamage = nullptr;
	if (DamageEvent.GetTypeID() == FSunsetDamageEvent::ClassID)
	{
		MyDamage = (FSunsetDamageEvent*)&DamageEvent;
	}
	// The damage event is a valid damage event for the game

	// Need to create a singletop which can get a multiplier of damage vs type of armor.
	// so it wont be reading an FTable for each time a unit takes damage.
	if (MyDamage)
	{
		float Multiplier = 1.f;
		USunsetGameInstance* SunsetGameInstance = Cast<USunsetGameInstance>(GetGameInstance());
		if (SunsetGameInstance)
		{
			Multiplier = SunsetGameInstance->GetArmorContribution(MyDamage->TypeOfAttack, ArmorType);
		}
		Health -= DamageAmount * Multiplier * DamageReduction;
	}

	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	if (Health <= 0.f)
	{
		KillMinion();
	}
	return DamageCaused;
}

void AMinion::UpdateDamageReduction()
{
	DamageReduction = 1 - (0.05f * Armor / (1 + 0.05f * FMath::Abs(Armor)  ));
}