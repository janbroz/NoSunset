// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MinionController.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API AMinionController : public AAIController
{
	GENERATED_BODY()

public:
	AMinionController();
	
	virtual void Possess(class APawn* InPawn) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit AI")
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit AI")
		class UBehaviorTreeComponent* BehaviorTreeComponent;
};
