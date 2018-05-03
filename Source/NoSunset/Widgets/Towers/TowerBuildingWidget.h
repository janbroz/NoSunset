// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "TowerBuildingWidget.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API UTowerBuildingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = UITalking)
		void UpdateMaskPercent(float NewPercent);
	
};
