// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayStats/SunsetAttribute.h"
#include "GameplayStats/SunsetEffect.h"
#include "SunsetAbilityComponent.generated.h"

class USunsetEffect;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOSUNSET_API USunsetAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USunsetAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void AddEffect(const TSubclassOf<USunsetEffect> NewEffectClass);

	UFUNCTION()
		void SayHey();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USunsetAttribute* AttributeSet;
	UPROPERTY(VisibleAnywhere)
		FActiveEffectsContainer EffectsManager;

};
