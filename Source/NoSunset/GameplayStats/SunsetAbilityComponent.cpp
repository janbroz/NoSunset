// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetAbilityComponent.h"
#include "GameplayStats/SunsetAttribute.h"
#include "GameplayStats/SunsetEffect.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USunsetAbilityComponent::USunsetAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	AttributeSet = CreateDefaultSubobject<USunsetAttribute>(TEXT("Attribute Set"));
	EffectsManager.OwnerAbilityComponent = this;
}


// Called when the game starts
void USunsetAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USunsetAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USunsetAbilityComponent::AddEffect(const TSubclassOf<USunsetEffect> NewEffectClass)
{
	if (NewEffectClass)
	{
		USunsetEffect* NewEffect = NewObject<USunsetEffect>(this, NewEffectClass);

		if (NewEffect)
		{
			FEffectSpec EffectDefinition(NewEffect);
			EffectsManager.AddEffect(NewEffect);
			//EffectsManager.ApplyEffectSpec(EffectDefinition);
			//AttributeSet->ApplyModifierEffect(EffectDefinition);

			UE_LOG(LogTemp, Warning, TEXT("The effect was created just nice, with: %f"), NewEffect->EffectValue);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("The effect was not created just nice"));
		}
	}
}

void USunsetAbilityComponent::SayHey()
{
	UE_LOG(LogTemp, Warning, TEXT("Delegate got called"));
}