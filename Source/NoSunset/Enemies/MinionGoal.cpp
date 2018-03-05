// Fill out your copyright notice in the Description page of Project Settings.

#include "MinionGoal.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
AMinionGoal::AMinionGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GoalZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Goal Zone"));
	GoalZone->SetupAttachment(RootComponent);
	GoalZone->SetBoxExtent(FVector(64.f, 64.f, 64.f));
}

// Called when the game starts or when spawned
void AMinionGoal::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void AMinionGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

