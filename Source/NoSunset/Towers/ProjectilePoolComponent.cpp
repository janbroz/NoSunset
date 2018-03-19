// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectilePoolComponent.h"
#include "DataStructures.h"
#include "Towers/Projectile.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UProjectilePoolComponent::UProjectilePoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectilePoolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnProjectileClasses();
}


// Called every frame
void UProjectilePoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectilePoolComponent::SpawnProjectileClasses()
{
	FString Sts = "/Game/Blueprints/Towers/Projectiles/Arrow_Projectile.Arrow_Projectile_C";
	UClass* BPClass = LoadObject<UClass>(NULL, *Sts, NULL, LOAD_None, NULL);
	TSubclassOf<AProjectile> ProjectileClass = BPClass;

	TArray<AProjectile*> TmpProjectileArray;
	FClassPoolArray PoolStructure;
	PoolStructure.ProjectileClass = ProjectileClass;
	//UE_LOG(LogTemp, Warning, TEXT("Went just right"));

	for (auto i = 0; i < 10; ++i)
	{
		AProjectile* PoolProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, FTransform());
		if (PoolProjectile)
		{
			//UE_LOG(LogTemp, Warning, TEXT("The class is valid"));
			PoolProjectile->SetProjectileEnabled(false);
			UGameplayStatics::FinishSpawningActor(PoolProjectile, PoolProjectile->GetTransform());
			PoolStructure.InstantiatedProjectiles.Add(PoolProjectile);
			PoolProjectile->SetFolderPath("/PoolingProjectiles/Arrows");
		}
	}
	ProjectilesPool.Add(PoolStructure);
}
