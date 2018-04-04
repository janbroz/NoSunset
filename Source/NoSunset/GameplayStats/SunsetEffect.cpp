// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetEffect.h"



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

FActiveEffect* FActiveEffectsContainer::ApplyEffectSpec(const FEffectSpec& Spec)
{
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