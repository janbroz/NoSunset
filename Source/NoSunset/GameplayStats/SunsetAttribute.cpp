// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetAttribute.h"
#include "GameplayStats/SunsetEffect.h"

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

void FAttributeData::ModifyBaseValue(float NewValue)
{
	// Do stuff like check if it goes below 0.
	BaseValue += NewValue;
}

void FAttributeData::ModifyCurrentValue(float NewValue, bool bHasMaxValue, float MaxValue)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Value is: %f"), NewValue);
	UE_LOG(LogTemp, Warning, TEXT("Current value is: %f"), CurrentValue);*/

	const float ModifiedValue = CurrentValue + NewValue;
	if (bHasMaxValue)
	{
		CurrentValue = FMath::Clamp(ModifiedValue, 0.f, MaxValue);
	}
	else
	{
		CurrentValue = FMath::Clamp(ModifiedValue, 0.f, ModifiedValue);
	}
	//UE_LOG(LogTemp, Warning, TEXT("new Value is: %f"), CurrentValue);
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
			//UE_LOG(LogTemp, Warning, TEXT("It is a valid property"));
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Awkward, It is not a valid property"));
		}
	}
	return false;
}


USunsetAttribute::USunsetAttribute()
{

}

USunsetAttribute::~USunsetAttribute()
{

}

FAttribute USunsetAttribute::HealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(USunsetAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(USunsetAttribute, Health));
	return FAttribute(Property);
}

//void USunsetAttribute::ApplyModifierEffect(USunsetEffect* EffectToApply)
//{
//	
//	UStructProperty* StructProperty = Cast<UStructProperty>(EffectToApply->Attribute.Attribute);
//	check(StructProperty);
//	FAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FAttributeData>(this);
//	if (ensure(DataPtr))
//	{
//		DataPtr->SetCurrentValue(EffectToApply->EffectValue);
//		
//		UE_LOG(LogTemp, Warning, TEXT("Stuff went fine and we should be modifiying some shit"));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Shiiiiet"));
//	}
//
//}