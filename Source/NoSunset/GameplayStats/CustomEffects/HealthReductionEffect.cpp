// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthReductionEffect.h"
#include "GameplayStats/SunsetAbilityComponent.h"
#include "Enemies/Minion.h"


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
	if (bEnabled && Owner && Owner->GetOwner())
	{
		/*AMinion* TargetMinion = Cast<AMinion>(Owner->GetOwner());
		if (TargetMinion)
		{
			TargetMinion->TakeDamage(CalculateEffect(),FSunsetDamageEvent(), nullptr, nullptr);
		}*/
		

		UProperty* ModifiedProperty = Attribute.GetUProperty();
		static UProperty* HealthProperty = FindFieldChecked<UProperty>(USunsetAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(USunsetAttribute, Health));
		//static UProperty* HealtyPropery = FindFieldChecked<UProperty>(USunsetAttribute::StaticClass(), GET_MEMBER_NAME_STRING_CHECKED(USunsetAttribute, Health));

		if (ModifiedProperty == HealthProperty)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Its gonna hurt babe!"));

			// this should be done via the take damage, so that our ui gets refreshed instantly.
			UStructProperty* StructProperty = Cast<UStructProperty>(Attribute.Attribute);
			check(StructProperty);
			FAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FAttributeData>(Owner->AttributeSet);
			if (ensure(DataPtr))
			{
				const float TotalChange = CalculateEffect();
				UE_LOG(LogTemp, Warning, TEXT("Current health is: %f"), DataPtr->CurrentValue);
				DataPtr->ModifyCurrentValue(TotalChange);
			}
		}
	}
}