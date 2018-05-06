// Fill out your copyright notice in the Description page of Project Settings.

#include "ConstructionGrid.h"
#include "Runtime/Engine/Classes/Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Runtime/Landscape/Classes/Landscape.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values
AConstructionGrid::AConstructionGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene component"));
	RootComponent = SceneComponent;
	InstancedMesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Instanced mesh"));
	InstancedMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AConstructionGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConstructionGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConstructionGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// ok, this is weird
	if (!InstancedMesh->GetStaticMesh()) return;
	InstancedMesh->ClearInstances();

	for (int32 i = 0; i <= GridWidth; i++)
	{
		for (int32 j = 0; j <= GridHeight; j++)
		{
			FVector NewLoc(0.f + i*100.f, 0.f + j*100.f, 0.f);
			//FVector EndLoc(0.f + i*100.f, 0.f + j*100.f, -200.f);

			FVector LineStart = GetActorLocation() + NewLoc;
			FVector LineEnd = LineStart + FVector(0, 0, -200.f);
			FHitResult Hit;
			FCollisionQueryParams FCQP;
			
			GetWorld()->LineTraceSingleByChannel(Hit, LineStart, LineEnd, ECollisionChannel::ECC_Visibility);
			DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, true, 0.09f, 0.f, 1.f);
			if (Hit.bBlockingHit)
			{
				ALandscape* TargetActor = Cast<ALandscape>(Hit.GetActor());
				if (TargetActor)
				{
					
					float HeightToLandscape = LineStart.Z - Hit.Location.Z;
					if (HeightToLandscape < 120.f)
					{
						FTransform NewTrans(NewLoc);
						InstancedMesh->AddInstance(NewTrans);
					}
				}
			}
		}
	}
}