// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveProjectile.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Enemies/Minion.h"

AExplosiveProjectile::AExplosiveProjectile()
{
	ExplosionRange = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionRange"));
	ExplosionRange->SetupAttachment(RootComponent);

}


void AExplosiveProjectile::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto MinionOverlapped = Cast<AMinion>(OtherActor);
	if (MinionOverlapped)
	{
		UE_LOG(LogTemp, Warning, TEXT("We got a minion"));
		TArray<AActor*> ActorsCaughtInExplosion;
		ExplosionRange->GetOverlappingActors(ActorsCaughtInExplosion, AMinion::StaticClass());

		for (auto &ActualActor : ActorsCaughtInExplosion)
		{
			auto* Minion = Cast<AMinion>(ActualActor);
			TestingEffects(Minion);
			
			FSunsetDamageEvent MyDamageEvent = FSunsetDamageEvent();
			MyDamageEvent.TypeOfAttack = DamageType;

			AController* Instigator = Cast<AController>(GetOwner());
			Minion->TakeDamage(Damage, MyDamageEvent, Instigator, SpawnedBy);
		}
		ApplyFX();
		DestroyProjectile();
	}
}

void AExplosiveProjectile::OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}