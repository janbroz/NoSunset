// Fill out your copyright notice in the Description page of Project Settings.

#include "Minion.h"
#include "Enemies/MinionController.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "GlobalEventHandler.h"
#include "SunsetGameState.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SunsetDamageType.h"
#include "SunsetGameInstance.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "Widgets/Enemies/EnemyHealthBarWidget.h"
#include "GameplayStats/SunsetAbilityComponent.h"

// Sets default values
AMinion::AMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<USunsetAbilityComponent>(TEXT("Ability system"));
	

	AIControllerClass = AMinionController::StaticClass();
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));

	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health bar widget"));
	HealthBarComponent->SetupAttachment(RootComponent);
	Health = 100.f;
	MaxHealth = Health;

	// Should be toggled by the player.
	bShowingHealthBar = true;
}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystem)
	{
		AbilitySystem->InitAttributeSet();
	}

	SpawnDefaultController();

	ASunsetGameState* SunsetGameState = Cast<ASunsetGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (SunsetGameState)
	{
		EventHandler = SunsetGameState->EventHandler;
	}
	UpdateDamageReduction();
	SetupUIHealth();
}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHealthBarLocation();
}

// Called to bind functionality to input
void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMinion::KillMinion(class AController* EventInstigator, AActor * DamageCauser)
{
	// Call either the wave spawner or the game state.

	//Minion_OnKilled.Broadcast(this, nullptr);
	EventHandler->OnMinionKilled.Broadcast(this, EventInstigator, DamageCauser);
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

	// Need to create a singleton which can get a multiplier of damage vs type of armor.
	// so it wont be reading an FTable for each time a unit takes damage.
	if (MyDamage)
	{
		float Multiplier = 1.f;
		USunsetGameInstance* SunsetGameInstance = Cast<USunsetGameInstance>(GetGameInstance());
		if (SunsetGameInstance)
		{
			Multiplier = SunsetGameInstance->GetArmorContribution(MyDamage->TypeOfAttack, ArmorType);
		}
		float TotalDamage = DamageAmount * Multiplier * DamageReduction;
		ModifyHealth(-TotalDamage);
	}

	if (!AbilitySystem || !AbilitySystem->AttributeSet) return 0;
	FAttributeData* HealthData = &AbilitySystem->AttributeSet->Health;
	if (HealthData->CurrentValue <= 0.f)
	{
		KillMinion(EventInstigator, DamageCauser);
	}

	return DamageCaused;
}

void AMinion::UpdateDamageReduction()
{
	DamageReduction = 1 - (0.05f * Armor / (1 + 0.05f * FMath::Abs(Armor)));
}

void AMinion::UpdateHealthBarLocation()
{
	HealthBarComponent->SetWorldRotation(FRotator(90.f,0.f, 0.f));
}

void AMinion::ModifyHealth(float Amount)
{
	// New health, now with stats!
	if (!AbilitySystem || !AbilitySystem->AttributeSet) return;
	FAttributeData* HealthData = &AbilitySystem->AttributeSet->Health;
	HealthData->ModifyCurrentValue(Amount);

	if (bShowingHealthBar)
	{
		UEnemyHealthBarWidget* HealthWidget = Cast<UEnemyHealthBarWidget>(HealthBarComponent->GetUserWidgetObject());
		if (HealthWidget)
		{
			HealthWidget->UpdateHealth(HealthData->GetCurrentValue());
		}
	}
}

void AMinion::SetupUIHealth()
{
	if (!AbilitySystem || !AbilitySystem->AttributeSet) return;
	FAttributeData* HealthData = &AbilitySystem->AttributeSet->Health;
	FAttributeData* MaxHealthData = &AbilitySystem->AttributeSet->MaxHealth;


	UEnemyHealthBarWidget* HealthWidget = Cast<UEnemyHealthBarWidget>(HealthBarComponent->GetUserWidgetObject());
	if (HealthWidget && HealthData && MaxHealthData)
	{
		HealthWidget->SetupHealth(HealthData->GetCurrentValue(), MaxHealthData->GetCurrentValue());
	}
}