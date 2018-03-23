// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Enemies/Minion.h"
#include "SunsetDamageType.h"
#include "Engine/World.h"
#include "SunsetGameState.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileBeginOverlap);
	ProjectileCollision->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnProjectileEndOverlap);
	RootComponent = ProjectileCollision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(ProjectileCollision);
	ProjectileMovement->InitialSpeed = 1200.f;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// This one is the default number of projectiles to spawn in the object pool.
	Rarity = 15;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//SetTimeToLive();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("El actor es: %s"), *OtherActor->GetName());

	auto MinionOverlapped = Cast<AMinion>(OtherActor);
	if (MinionOverlapped)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Valid stuff"));
		FSunsetDamageEvent MyDamageEvent = FSunsetDamageEvent();
		MyDamageEvent.TypeOfAttack = DamageType;

		AController* Instigator = Cast<AController>(GetOwner());
		MinionOverlapped->TakeDamage(Damage, MyDamageEvent, Instigator, SpawnedBy);
		
		DestroyProjectile();
		//if (Target && Target == MinionOverlapped)
		//{
		//	// At this point we should apply the damage to the minion and do something if the attack is 
		//	// supposed to do AOE or apply a DoT.
		//	//Target->TakeDamage(Damage, FDamageEvent(DamageClass), nullptr, this);

		//}
		//else
		//{
		//	// Should we do something? Cause we just hit a minion that is not our target.
		//}
	}
}

void AProjectile::OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AProjectile::SetTimeToLive()
{
	GetWorldTimerManager().SetTimer(TTLHandler, this, &AProjectile::DestroyProjectile, 2.f, false);
}

void AProjectile::DestroyProjectile()
{
	// Do stuff like explode or dissapear.
	SetProjectileEnabled(false);
	//Destroy();
}

void AProjectile::SetupProjectileDamage(EElementType DamageType, float Damage, TSubclassOf<USunsetDamageType> DamageClass)
{
	this->Damage = Damage;
	this->DamageType = DamageType;
	this->DamageClass = DamageClass;
}

void AProjectile::SetupProjectileAsHoming(USceneComponent* Target)
{
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingTargetComponent = Target;
	ProjectileMovement->HomingAccelerationMagnitude = 20000.f;
	ProjectileMovement->MaxSpeed = 1600.f;
}

void AProjectile::SetProjectileEnabled(bool bIsEnabled)
{
	//UE_LOG(LogTemp, Warning, TEXT("Projectile should be disabled"));
	if (bIsEnabled)
	{
		SetActorHiddenInGame(false);
		ProjectileMovement->SetActive(true);
		ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		ProjectileCollision->SetActive(true);
		SetTimeToLive();
	}
	else
	{
		ASunsetGameState* GameState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
		GameState->AddProjectileToPool(this);

		ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ProjectileMovement->SetActive(false);
		ProjectileCollision->SetActive(false);
		SetActorHiddenInGame(true);
	}
}