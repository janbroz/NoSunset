// Fill out your copyright notice in the Description page of Project Settings.

#include "Minion.h"
#include "Enemies/MinionController.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "GlobalEventHandler.h"
#include "SunsetGameState.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SunsetDamageType.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Nigga, someone hit me"));
	float DamageCaused = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageAmount;

	USunsetDamageType* DamageType = Cast<USunsetDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());
	if (DamageType)
	{
		if (DamageType->DamageType == EElementType::Fire)
		{
			UE_LOG(LogTemp, Warning, TEXT("and its hot!"));
		}
		if (DamageType->DamageType == EElementType::Physical)
		{
			UE_LOG(LogTemp, Warning, TEXT("and its hard!"));
		}
	}
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	if (Health <= 0.f)
	{
		KillMinion();
	}
	return DamageCaused;
}