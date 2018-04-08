// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthReductionEffect.h"
#include "GameplayStats/SunsetAbilityComponent.h"



UHealthReductionEffect::UHealthReductionEffect()
{
	static UProperty* HealthProperty = FindFieldChecked<UProperty>(USunsetAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(USunsetAttribute, Health));
	if (HealthProperty)
	{
		FAttribute Att(HealthProperty);
		Attribute = Att;
	}

}

void UHealthReductionEffect::ApplyEffect()
{
	if (Owner && Owner->GetOwner())
	{
		UProperty* ModifiedProperty = Attribute.GetUProperty();
		static UProperty* HealthProperty = FindFieldChecked<UProperty>(USunsetAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(USunsetAttribute, Health));

		if (ModifiedProperty == HealthProperty)
		{
			UE_LOG(LogTemp, Warning, TEXT("Its gonna hurt babe!"));
			UStructProperty* StructProperty = Cast<UStructProperty>(Attribute.Attribute);
			check(StructProperty);
			FAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FAttributeData>(Owner->AttributeSet);
			if (ensure(DataPtr))
			{
				const float Val = DataPtr->CurrentValue;
				DataPtr->SetCurrentValue(Val + EffectValue);
			}
		}
	}
}