// Fill out your copyright notice in the Description page of Project Settings.

#include "MinionController.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SunsetGameState.h"
#include "Enemies/WaveSpawner.h"
#include "Enemies/MinionGoal.h"


AMinionController::AMinionController()
{
	//BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("UnitAIComponent"));
	//BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("UnitBehaviorTree"));
	BrainComponent = BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Unit brain"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Brain blackboard"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Tree_BP(TEXT("/Game/Blueprints/Minions/AI/Minion_BT"));
	if (Tree_BP.Object != nullptr)
	{
		BehaviorTree = Tree_BP.Object;
	}

}

void AMinionController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (BehaviorTree)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*BehaviorTree, EBTExecutionMode::Looped);

		FVector SpawnerLocation = FVector::ZeroVector;
		ASunsetGameState* GameState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
		if (GameState && GameState->LevelGoalZone)
		{
			//SpawnerLocation = GameState->LevelWaveSpawner->GetActorLocation();
			SpawnerLocation = GameState->LevelGoalZone->GetActorLocation();
		}
		Blackboard->SetValueAsVector(TEXT("Destiny"), SpawnerLocation);
	}
}