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
			bool bSuccesfullyAdded = EffectsManager.AddEffect(NewEffect);
			if (bSuccesfullyAdded)
			{
				ApplyEffect(NewEffect);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Effect already got applied"));
			}
		}
	}
}

void USunsetAbilityComponent::ApplyEffect(USunsetEffect* EffectToApply)
{
	//UE_LOG(LogTemp, Warning, TEXT("Effect got applied"));
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(EffectToApply->PeriodHandle, EffectToApply, &USunsetEffect::ApplyEffect, 0.5f, true, 0.f);
	TimerManager.SetTimer(EffectToApply->DurationHandle, EffectToApply, &USunsetEffect::ClearEffect, EffectToApply->Duration, false, -1.f);
}


void USunsetAbilityComponent::SayHey()
{
	UE_LOG(LogTemp, Warning, TEXT("Delegate got called"));
}