// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetAbilityComponent.h"
#include "GameplayStats/SunsetAttribute.h"

// Sets default values for this component's properties
USunsetAbilityComponent::USunsetAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	AttributeSet = CreateDefaultSubobject<USunsetAttribute>(TEXT("Attribute Set"));
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

