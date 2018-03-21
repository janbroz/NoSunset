// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectilePoolComponent.h"
#include "DataStructures.h"
#include "Towers/Projectile.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/ObjectLibrary.h"

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
	//GetAllProjectileNames();
}


// Called every frame
void UProjectilePoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectilePoolComponent::SpawnProjectileClasses()
{
	//FString Sts = "/Game/Blueprints/Towers/Projectiles/Arrow_Projectile.Arrow_Projectile_C";
	//UClass* BPClass = LoadObject<UClass>(NULL, *Sts, NULL, LOAD_None, NULL);	
	//TSubclassOf<AProjectile> ProjectileClass = BPClass;
	
	TArray<FString> ProjectileClassesStrings = GetAllProjectileNames();
	TArray<UClass*> ProjectileClasses;

	for (auto ClassRoute : ProjectileClassesStrings)
	{
		TSubclassOf<AProjectile> ProjectileClass = LoadClass<AProjectile>(NULL, *ClassRoute, NULL, LOAD_None, NULL);
		auto DefaultProjectile = ProjectileClass.GetDefaultObject();
		if (DefaultProjectile)
		{
			TArray<AProjectile*> TmpProjectileArray;
			FClassPoolArray PoolStructure;
			PoolStructure.ProjectileClass = ProjectileClass;
			//UE_LOG(LogTemp, Warning, TEXT("Went just right"));

			int32 Rarity = DefaultProjectile->Rarity;

			for (auto i = 0; i < Rarity; ++i)
			{
				AProjectile* PoolProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, FTransform());
				if (PoolProjectile)
				{
					//UE_LOG(LogTemp, Warning, TEXT("The class is valid"));
					//PoolProjectile->SetProjectileEnabled(false);
					UGameplayStatics::FinishSpawningActor(PoolProjectile, PoolProjectile->GetTransform());
					PoolStructure.InstantiatedProjectiles.Add(PoolProjectile);
					PoolProjectile->SetFolderPath("/PoolingProjectiles/Arrows");
					PoolProjectile->SetProjectileEnabled(false);
				}
			}
			PoolOfProjectiles.Add(PoolStructure);
		}
	}
}

AProjectile* UProjectilePoolComponent::GetUsableProjectile(TSubclassOf<AProjectile> ProjectileClass)
{
	FClassPoolArray* UsableProjectileStruct();
	AProjectile* ChosenProjectile = nullptr;

	for (auto &RightStruct : PoolOfProjectiles)
	{
		if (RightStruct.ProjectileClass == ProjectileClass)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Usable projectiles class here"));
			if (RightStruct.InstantiatedProjectiles.Num() > 0)
			{
				ChosenProjectile = RightStruct.InstantiatedProjectiles[0];
				RightStruct.InstantiatedProjectiles.RemoveAt(0);
			}
			break;
		}
	}
	return ChosenProjectile;
}

bool UProjectilePoolComponent::AddProjectileToPool(AProjectile* ProjectileToAdd)
{
	TSubclassOf<AProjectile> ProjectileClass =  ProjectileToAdd->GetClass();
	for (auto &ProjectileStruct : PoolOfProjectiles)
	{
		if (ProjectileStruct.ProjectileClass == ProjectileClass)
		{
			ProjectileStruct.InstantiatedProjectiles.AddUnique(ProjectileToAdd);
			break;
		}
	}
	return true;
}

TArray<FString> UProjectilePoolComponent::GetAllProjectileNames()
{
	// Well shit, this only works for primary assets (levels).

	auto ObjectLibrary = UObjectLibrary::CreateLibrary(UBlueprint::StaticClass(), false, true);
	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Blueprints/Towers/Projectiles"));
	TArray<FAssetData> AssetData;
	ObjectLibrary->GetAssetDataList(AssetData);

	UE_LOG(LogTemp, Warning, TEXT("Found those assets: %d"), AssetData.Num());
	TArray<FString> Names = TArray<FString>();

	for (auto AData : AssetData)
	{
		

		auto Name = AData.ToStringReference().ToString().Append("_C");
		Names.Add(Name);
		UE_LOG(LogTemp, Warning, TEXT("The stuff is: %s"), *Name);
	}

	return Names;
}