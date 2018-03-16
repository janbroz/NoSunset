// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ASunsetPlayerState::ASunsetPlayerState()
{
	PlayerName = TEXT("Default Player");
	Gold = 100;
	SpecialResource = 0;
	CurrentLives = 30;
	MaxLives = CurrentLives;
}


void ASunsetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASunsetPlayerState, Gold);
	DOREPLIFETIME(ASunsetPlayerState, SpecialResource);
	DOREPLIFETIME(ASunsetPlayerState, MaxLives);
	DOREPLIFETIME(ASunsetPlayerState, CurrentLives);
}

void ASunsetPlayerState::DamagePlayer(int32 Damage)
{
	CurrentLives -= Damage;
	CurrentLives = FMath::Clamp(CurrentLives, 0, MaxLives);

	if (CurrentLives <= 0)
	{
		auto Controller = Cast<APlayerController>(GetOwner());
		if (Controller)
		{
			UE_LOG(LogTemp, Warning, TEXT("Its a valid actor"));
			//Controller->SetPause(true);
		}
	}
}

void ASunsetPlayerState::ModifyGold(int32 Amount)
{
	Gold += Amount; 

}