// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetEffect.h"
#include "GameplayStats/SunsetAbilityComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Engine/World.h"

FActiveEffectsContainer::FActiveEffectsContainer()
{
	NumberOfEffects = 0.0f;

}


FActiveEffectsContainer::~FActiveEffectsContainer()
{

}

void FActiveEffectsContainer::AddEffect(USunsetEffect* NewEffect)
{
	AppliedEffects.Add(NewEffect);
	NewEffect->SetOwner(OwnerAbilityComponent);
	NumberOfEffects = AppliedEffects.Num();
}

void USunsetEffect::SetOwner(USunsetAbilityComponent* NewOwner)
{
	Owner = NewOwner;
}

USunsetEffect::USunsetEffect()
	: Owner(nullptr)
{

}

void USunsetEffect::ApplyEffect()
{
	if (Owner && Owner->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hey there, i am: %s"), *GetName());

		

	}
}

void USunsetEffect::ClearEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("Effect is over, nothing to see here"));
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
/*
	PeriodHandle.Invalidate();
	DurationHandle.Invalidate();*/
}

void USunsetEffect::SayHey()
{
	if (Owner && Owner->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hey there, i am: %s"), *GetName());
	}
}