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

bool FActiveEffectsContainer::AddEffect(USunsetEffect* NewEffect)
{
	// How to add a effect to the active effects queue
	bool bEffectExists = AppliedEffects.ContainsByPredicate(
		[&](const UObject* Object)
		{
		return Object->GetClass() == NewEffect->GetClass();
		});

	// We know there is an item of similar class. Is there a way to
	// get the item without using an array iterator? Stay with us and
	// watch it on the next episode!

	if (bEffectExists && OwnerAbilityComponent)
	{
		USunsetEffect* StackingEffect = nullptr;
		for (auto Eff : AppliedEffects)
		{
			if (Eff->GetClass() == NewEffect->GetClass())
			{
				StackingEffect = Eff;
				break;
			}
		}

		if (StackingEffect)
		{
			FTimerManager& TimerManager = OwnerAbilityComponent->GetWorld()->GetTimerManager();
			if (StackingEffect->StackCount < StackingEffect->MaxStackAmount)
			{
				StackingEffect->StackCount++;
				
			}
			TimerManager.SetTimer(StackingEffect->DurationHandle, StackingEffect, &USunsetEffect::ClearEffect, StackingEffect->Duration, false, -1.0f);	
			TimerManager.SetTimer(StackingEffect->PeriodHandle, StackingEffect, &USunsetEffect::ApplyEffect, StackingEffect->Period, true, -1.0f);
			TimerManager.SetTimer(StackingEffect->StackHandle, StackingEffect, &USunsetEffect::ClearStack, StackingEffect->StackDuration, false, -1.0f);
		}

		UE_LOG(LogTemp, Warning, TEXT("There is a similar effect"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is not a similar effect, buu!"));
		AppliedEffects.Add(NewEffect);
		NewEffect->SetOwner(OwnerAbilityComponent);
		NewEffect->bEnabled = true;
		NumberOfEffects = AppliedEffects.Num();
	}

	return !bEffectExists;
}

void USunsetEffect::ClearStack()
{
	StackCount--;
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
	bEnabled = false;
	UE_LOG(LogTemp, Warning, TEXT("Effect is over, nothing to see here"));
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	if (Owner)
	{
		Owner->EffectsManager.AppliedEffects.Remove(this);
	}
    /*PeriodHandle.Invalidate();
	DurationHandle.Invalidate();*/
}

void USunsetEffect::SayHey()
{
	if (Owner && Owner->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hey there, i am: %s"), *GetName());
	}
}

float USunsetEffect::CalculateEffect()
{
	// Calculate the real effect after modifications like stacks and stuff.
	return EffectValue;
}