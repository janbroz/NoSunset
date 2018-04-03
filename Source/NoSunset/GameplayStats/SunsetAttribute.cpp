// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetAttribute.h"


float FAttributeData::GetCurrentValue() const
{
	return CurrentValue;
}

void FAttributeData::SetCurrentValue(float NewValue)
{
	CurrentValue = NewValue;
}

float FAttributeData::GetBaseValue() const
{
	return BaseValue;
}

void FAttributeData::SetBaseValue(float NewValue)
{
	BaseValue = NewValue;
}

FAttribute::FAttribute(UProperty* NewProperty)
{
	Attribute = nullptr;
	AttributeOwner = nullptr;

	if (IsAttributeDataProperty(NewProperty))
	{
		Attribute = NewProperty;
	}
}

bool FAttribute::IsAttributeDataProperty(const UProperty* Property)
{
	const UStructProperty* StructProp = Cast<UStructProperty>(Property);
	if (StructProp)
	{
		const UStruct* Struct = StructProp->Struct;
		if (Struct && Struct->IsChildOf(FAttributeData::StaticStruct()))
		{
			return true;
		}
	}
	return false;
}


USunsetAttribute::USunsetAttribute()
{

}

FAttribute USunsetAttribute::HealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(USunsetAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(USunsetAttribute, Health));
	return FAttribute(Property);
}