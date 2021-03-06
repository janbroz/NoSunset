// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Enemies/Minion.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Towers/Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SunsetDamageType.h"
#include "Engine/World.h"
#include "SunsetGameState.h"
#include "Towers/ProjectilePoolComponent.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
#include "Widgets/Towers/TowerBuildingWidget.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene comp"));
	RootComponent = SceneComp;

	PlacementBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlacementBox"));
	PlacementBox->SetupAttachment(RootComponent);
	PlacementBox->SetBoxExtent(FVector(49.f, 49.f, 49.f));
	PlacementBox->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnBoxBeginOverlap);
	PlacementBox->OnComponentEndOverlap.AddDynamic(this, &ATower::OnBoxEndOverlap);

	RangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Range sphere"));
	RangeSphere->SetSphereRadius(AttackRange);
	RangeSphere->SetupAttachment(RootComponent);
	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnEnemyBeginOverlap);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATower::OnEnemyEndOverlap);

	TowerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Base"));
	TowerBase->SetupAttachment(RootComponent);
	
	TowerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Head"));
	TowerHead->SetupAttachment(TowerBase);

	TowerCanon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Canon"));
	TowerCanon->SetupAttachment(TowerHead);

	ProjectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile spawn location"));
	ProjectileSpawnLocation->SetupAttachment(TowerCanon);

	RangeDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Range Decal"));
	RangeDecalComponent->SetupAttachment(RootComponent);
	RangeDecalComponent->DecalSize = FVector(200.f, AttackRange, AttackRange);
	RangeDecalComponent->SetWorldRotation(FRotator(90.f, 0.f, 0.f));

	TowerBuildingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tower building widget"));
	TowerBuildingWidget->SetupAttachment(RootComponent);
	TowerBuildingWidget->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
	TowerBuildingWidget->SetDrawAtDesiredSize(true);
	TowerBuildingWidget->SetVisibility(false);

	bCanAttack = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterial_BP(TEXT("/Game/Materials/Range_Mat.Range_Mat"));
	if (DecalMaterial_BP.Object)
	{
		RangeDecalComponent->SetMaterial(0, DecalMaterial_BP.Object);
	}
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	RangeSphere->SetSphereRadius(AttackRange);

	if (ProjectileClass)
	{
		bUsesProjectiles = true;
	}

	GameState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
	RangeDecalComponent->DecalSize = FVector(200.f, AttackRange, AttackRange);

	BuildingMaterialInstance = UMaterialInstanceDynamic::Create(BuildingMaterial, this);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTurret();
}

void ATower::OnEnemyBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto MinionEnemy = Cast<AMinion>(OtherActor);
	if (Target == nullptr && MinionEnemy)
	{
		Target = MinionEnemy;
	}
}

void ATower::OnEnemyEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto MinionEnemy = Cast<AMinion>(OtherActor);
	if (Target == MinionEnemy)
	{
		GetANewTarget();
	}
}

void ATower::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UBoxComponent* Boxxy = Cast<UBoxComponent>(OtherComp);
	if (Boxxy)
	{
		bIsOverlappingWhileBuilding = true;
	}
}

void ATower::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UBoxComponent* Boxxy = Cast<UBoxComponent>(OtherComp);
	if (Boxxy)
	{
		bIsOverlappingWhileBuilding = false;
	}
}


void ATower::GetANewTarget()
{
	TArray<AActor*> OverlapingMinions;
	RangeSphere->GetOverlappingActors(OverlapingMinions, AMinion::StaticClass());
	
	/*int32 Elem = OverlapingMinions.Num();
	if (Elem > 0)
	{
		int32 RandTarget = FMath::RandHelper(Elem - 1);
		Target = Cast<AMinion>(OverlapingMinions[RandTarget]);
	}*/

	// This way we search for the closest enemy.
	// Use the commented code if you want to grab a random enemy
	AActor* ClosestMinion = nullptr;
	for (auto TmpMinion : OverlapingMinions)
	{
		if (ClosestMinion)
		{
			float DistToFirst = FVector::Dist(ClosestMinion->GetActorLocation(), GetActorLocation());
			float DistToSecond = FVector::Dist(TmpMinion->GetActorLocation(), GetActorLocation());
			ClosestMinion = DistToFirst <= DistToSecond ? ClosestMinion : TmpMinion;
		}
		else
		{
			ClosestMinion = TmpMinion;
		}
	}
	Target = Cast<AMinion>(ClosestMinion);
}

void ATower::AimTurret()
{
	if (Target)
	{
		// Rotate towards
		FRotator NewRot = (Target->GetActorLocation() - TowerHead->GetComponentLocation()).Rotation();
		TowerHead->SetWorldRotation(NewRot);
		if (bCanAttack)
		{
			Attack();
		}
	}
}

void ATower::Attack()
{	
	if (Target)
	{		
		if (bUsesProjectiles)
		{
			UE_LOG(LogTemp, Warning, TEXT("We can attack and use projectiles"));
			if (GameState && ProjectileClass && GameState->ProjectilePoolManager)
			{
				UE_LOG(LogTemp, Warning, TEXT("Stuff is good"));
				AProjectile* Projectile = GameState->ProjectilePoolManager->GetUsableProjectile(ProjectileClass);
				if (Projectile)
				{
					UE_LOG(LogTemp, Warning, TEXT("We found a projetile from the pool manager"));
					Projectile->SetActorTransform(ProjectileSpawnLocation->GetComponentTransform());
					Projectile->SetOwner(GetOwner());
					Projectile->SpawnedBy = this;
					Projectile->SetupProjectileDamage(AttackType, AttackDamage, DamageType);
					Projectile->SetupProjectileAsHoming(Target->GetRootComponent());
					Projectile->SetProjectileEnabled(true);

					bCanAttack = false;
					GetWorldTimerManager().SetTimer(AttackHandler, this, &ATower::Reload, AttackSpeed, false);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("The pool has no boombs"));
					// This means the pool is out of projectiles. Should spawn a 20% - 30% more and do another call to the get projectile.
				}
			}
		}
		else
		{
			// This means the tower does an insta attack and should use other type of effect or asset.
		}
	}
}

void ATower::Reload()
{
	// Run the reload animation and stuff related.
	bCanAttack = true;
}

void ATower::SetTowerMode(ETowerMode Mode)
{
	switch (Mode)
	{
	case ETowerMode::Placing:
		RangeSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TowerBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TowerHead->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TowerCanon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ToggleRangeIndicator(true);
		break;
	case ETowerMode::Building:
		BeginTowerBuilding();
		ToggleRangeIndicator(false);
		TowerBase->SetCollisionProfileName("TowerVisibility");
		TowerHead->SetCollisionProfileName("TowerVisibility");
		TowerCanon->SetCollisionProfileName("TowerVisibility");
		break;
	case ETowerMode::Working:
		RangeSphere->SetCollisionProfileName("TowerCollision");
		break;
	case ETowerMode::Upgrading:
		break;
	default:
		break;
	}
}

void ATower::BeginTowerBuilding()
{
	TowerBuildingWidget->SetVisibility(true);
	GetWorldTimerManager().SetTimer(BuildTimerHandle, this, &ATower::EndTowerBuilding, BuildingTime);
	
	GetWorldTimerManager().SetTimer(BuildingCooldownHandle, this, &ATower::UpdateBuildingWidget, GetWorld()->GetDeltaSeconds(), true, 0.0f);
}

void ATower::EndTowerBuilding()
{
	TowerBuildingWidget->SetVisibility(false);
	SetTowerMode(ETowerMode::Working);
	GetWorldTimerManager().ClearTimer(BuildingCooldownHandle);
}

void ATower::ToggleRangeIndicator(bool bShowRange)
{
	bShowingRangeIndicator = bShowRange;
	
	RangeDecalComponent->SetActive(bShowingRangeIndicator);
	RangeDecalComponent->SetHiddenInGame(!bShowingRangeIndicator);
}

void ATower::DrawRangeIndicator()
{
	//DrawDebugLine(GetWorld(),ProjectileSpawnLocation->GetComponentLocation() , Target->GetActorLocation(), FColor::Red, false, 0.03f, 8, 2.f);
	DrawDebugSphere(GetWorld(), GetActorLocation(), AttackRange, 32, FColor::Red, false, 0.033f, 8, 2.f);
	//UE_LOG(LogTemp, Warning, TEXT("Drawing a line, shalala"));
}

void ATower::UpdateBuildingWidget()
{
	float RemainingTime = GetWorldTimerManager().GetTimerRemaining(BuildTimerHandle);
	float RemainingPercent = 1- (RemainingTime / BuildingTime);
	UTowerBuildingWidget* BuildingWiget =  Cast<UTowerBuildingWidget>(TowerBuildingWidget->GetUserWidgetObject());
	
	if (BuildingWiget)
	{
		BuildingWiget->UpdateMaskPercent(RemainingPercent);
	}
}

void ATower::SetMaterialMode(EBuildLocation Location)
{
	switch (Location)
	{
	case EBuildLocation::Right:
		BuildingMaterialInstance->SetScalarParameterValue("ColorPercent", 1.f);
		TowerBase->SetMaterial(0, BuildingMaterialInstance);
		break;
	case EBuildLocation::Wrong:
		BuildingMaterialInstance->SetScalarParameterValue("ColorPercent", 0.f);
		TowerBase->SetMaterial(0, BuildingMaterialInstance);
		break;
	case EBuildLocation::Working:
		TowerBase->SetMaterial(0, StandardMaterial);
		break;
	default:
		break;
	}

}