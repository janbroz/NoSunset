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

void FActiveEffectsContainer::AddEffect(const FEffectSpec& NewEffect)
{
	ActiveEffects_Def.Add(NewEffect);
	NumberOfEffects = ActiveEffects_Def.Num();

	
	//NumberOfEffects++;

}

FActiveEffectHandle FActiveEffectHandle::GenerateNewHandle(USunsetAbilityComponent* OwningComp)
{
	static int32 GHandle = 0;
	FActiveEffectHandle NewHandle(GHandle++);

	// Handlers should be stored globally
	// TODO, read about the global active handlers


	return NewHandle;
}

USunsetAbilityComponent* FActiveEffectHandle::GetOwningAbilitySystem()
{
	//TODO - Write some code here
	return nullptr;
}


FActiveEffect* FActiveEffectsContainer::ApplyEffectSpec(const FEffectSpec& Spec)
{
	//Spec.EffectDefinition->Attribute;

	FActiveEffect* AppliedActiveEffect = nullptr;
	FActiveEffectHandle NewHandle = FActiveEffectHandle::GenerateNewHandle(OwnerAbilityComponent);

	if (OwnerAbilityComponent)
	{
		FTimerManager& TimerManager = OwnerAbilityComponent->GetWorld()->GetTimerManager();
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(OwnerAbilityComponent, &USunsetAbilityComponent::SayHey);
	}

	return nullptr;
}

USunsetEffect::USunsetEffect()
{

}

FEffectSpec::FEffectSpec()
{

}

FEffectSpec::FEffectSpec(const USunsetEffect* InDef)
{
	EffectDefinition = InDef;
}

void FEffectSpec::ApplyEffect()
{
	
	if (OwnerAbilityComponent)
	{
		/*OwnerAbilityComponent->AttributeSet->ApplyModifierEffect(*this);
		FTimerHandle Handy = FTimerHandle();
		OwnerAbilityComponent->GetWorld()->GetTimerManager().SetTimer(Handy, this, &FEffectSpec::ApplyEffect, 2.f, false);*/
		//OwnerAbilityComponent->GetWorld()->GetTimerManager().SetTimer(THandle, this, &FEffectSpec::ApplyEffect, 1.0f, false, 1.0f);
	}
}

FActiveEffect::FActiveEffect(const FActiveEffect& Other)
{
	*this = Other;
}

FActiveEffect::FActiveEffect(FActiveEffect&& Other)
	: Handle(Other.Handle)
{
	
}

FActiveEffect& FActiveEffect::operator=(FActiveEffect&& Other)
{
	Handle = Other.Handle;

	return *this;
}

FActiveEffect& FActiveEffect::operator=(const FActiveEffect& Other)
{
	Handle = Other.Handle;

	return *this;
}