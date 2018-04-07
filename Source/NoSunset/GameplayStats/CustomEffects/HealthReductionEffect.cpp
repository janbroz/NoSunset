// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthReductionEffect.h"




UHealthReductionEffect::UHealthReductionEffect()
{
	static UProperty* HealthProperty = FindFieldChecked<UProperty>(USunsetAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(USunsetAttribute, Health));
	if (HealthProperty)
	{
		FAttribute Att(HealthProperty);

		FModifierInfo NewModInfo = FModifierInfo();
		NewModInfo.Attribute = Att;
		NewModInfo.Magnitude = 1.f;
		
		Modifiers.Add(NewModInfo);

		Attribute = Att;
	}

}