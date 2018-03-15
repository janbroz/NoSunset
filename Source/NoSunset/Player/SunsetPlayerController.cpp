// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetPlayerController.h"
#include "Player/SunsetPawn.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Widgets/PlayerHUD/PlayerHUDWidget.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Towers/Tower.h"
#include "Player/SunsetPlayerState.h"

ASunsetPlayerController::ASunsetPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> PlayerHUD_BP(TEXT("/Game/UI/HUD/PlayerHUD_BP.PlayerHUD_BP_C"));
	if (PlayerHUD_BP.Object)
	{
		PlayerHUDClass = PlayerHUD_BP.Object;
	}
}


void ASunsetPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("VerticalMov", this, &ASunsetPlayerController::VerticalMovement);
	InputComponent->BindAxis("HorizontalMov", this, &ASunsetPlayerController::HorizontalMovement);

	InputComponent->BindAction("LMB", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::LeftMousePressed);
	InputComponent->BindAction("RMB", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::RightMousePressed);
	InputComponent->BindAction("LMB", EInputEvent::IE_Released, this, &ASunsetPlayerController::LeftMouseReleased);
	InputComponent->BindAction("RMB", EInputEvent::IE_Released, this, &ASunsetPlayerController::RightMouseReleased);
	InputComponent->BindAction("ToggleBuilding", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::ToggleBuilding);
	InputComponent->BindAction("ToggleMainMenu", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::ToggleMainMenu);
}

void ASunsetPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ThePlayerPawn = Cast<ASunsetPawn>(GetPawn());

	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UPlayerHUDWidget>(this, PlayerHUDClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}
}

void ASunsetPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckBuilding();

}

void ASunsetPlayerController::VerticalMovement(float Amount)
{
	if (ThePlayerPawn && Amount != 0.f)
	{
		FVector NewLocation = ThePlayerPawn->GetActorLocation();
		NewLocation += GetActorForwardVector() * 15.f * Amount;
		ThePlayerPawn->SetActorLocation(NewLocation);

		//UE_LOG(LogTemp, Warning, TEXT("Vertical"));
	}
}

void ASunsetPlayerController::HorizontalMovement(float Amount)
{
	if (ThePlayerPawn && Amount != 0.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Horizontal"));
		FVector NewLocation = ThePlayerPawn->GetActorLocation();
		NewLocation += GetActorRightVector() * 15.f * Amount;
		ThePlayerPawn->SetActorLocation(NewLocation);
	}
}

void ASunsetPlayerController::LeftMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Left mouse did something"));
	bLeftMousePressed = true;
}

void ASunsetPlayerController::RightMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Right mouse did something"));
	bRightMousePressed = true;
}

void ASunsetPlayerController::LeftMouseReleased()
{
	bLeftMousePressed = false;

	if (bBuilding && SpawningTower)
	{
		SpawningTower->SetTowerMode(ETowerMode::Building);
		SpawningTower = nullptr;
	}
}

void ASunsetPlayerController::RightMouseReleased()
{
	bRightMousePressed = false;
}

void ASunsetPlayerController::ToggleBuilding()
{
	bBuilding = !bBuilding;

	if (!bBuilding && SpawningTower)
	{
		ReimburseTowerCost(SpawningTower);
	}
}

void ASunsetPlayerController::ToggleMainMenu()
{

}

void ASunsetPlayerController::CheckBuilding()
{
	if (bBuilding)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_PhysicsBody, true, Hit);

		FName BuildTag = FName(TEXT("BuildingZone"));

		if (!Hit.bBlockingHit) return;
		FVector SnapLocation = SnapCoordinates(Hit.Location);
		if (SpawningTower)
		{
			SpawningTower->SetActorLocation(SnapLocation);
		}

		if (Hit.bBlockingHit && Hit.Actor->ActorHasTag(BuildTag))
		{
			//UE_LOG(LogTemp, Warning, TEXT("The actor is: %s"), *Hit.Actor->GetName());
			DrawDebugBox(GetWorld(), SnapLocation, FVector(50.f, 50.f, 50.f), FColor::Green, false, 0.03f, 2, 2.f);
			bValidSurfaceForBuilding = true;
		}
		else
		{
			DrawDebugBox(GetWorld(), SnapLocation, FVector(50.f, 50.f, 50.f), FColor::Red, false, 0.03f, 2, 2.f);
			bValidSurfaceForBuilding = false;
		}
	}

}

FVector ASunsetPlayerController::SnapCoordinates(FVector InitialCoords)
{
	float X, Y;
	X = (int)(InitialCoords.X / 25) * 25;
	Y = (int)(InitialCoords.Y / 25) * 25;
	return FVector(X, Y, InitialCoords.Z);
}

bool ASunsetPlayerController::SpawnTowerFromClass(UClass* ClassToSpawn)
{
	if (!bBuilding) return false;
	if (SpawningTower)
	{
		ReimburseTowerCost(SpawningTower);
	}

	TSubclassOf<ATower> TowerClass = ClassToSpawn;
	auto DefaultTower = TowerClass.GetDefaultObject();

	bool bHasTheMoney = DoesPlayerHasTheMoney(TowerClass);
	if (!bHasTheMoney || !DefaultTower) return false;

	FActorSpawnParameters FASP;
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit)
	{
		FVector MouseAt = Hit.Location;
		SpawningTower = GetWorld()->SpawnActor<ATower>(TowerClass, MouseAt, FRotator::ZeroRotator, FASP);
	}
	else
	{
		SpawningTower = GetWorld()->SpawnActor<ATower>(TowerClass, FVector::ZeroVector, FRotator::ZeroRotator, FASP);
	}
	if (SpawningTower)
	{
		SpawningTower->SetOwner(this);
		UE_LOG(LogTemp, Warning, TEXT("My owner is: %s"), *SpawningTower->GetOwner()->GetName());
		ASunsetPlayerState* SPlayerState = Cast<ASunsetPlayerState>(PlayerState);
		if (SPlayerState)
		{
			SPlayerState->ModifyGold(-DefaultTower->Cost);
		}
	}
	return SpawningTower ? true : false;
}

bool ASunsetPlayerController::DoesPlayerHasTheMoney(TSubclassOf<ATower> ClassToBuild)
{
	int32 Cost;
	ASunsetPlayerState* SPlayerState = Cast<ASunsetPlayerState>(PlayerState);
	if (!SPlayerState) return false;

	auto DefaultTower = ClassToBuild.GetDefaultObject();
	if (DefaultTower)
	{
		Cost = DefaultTower->Cost;
		return SPlayerState->Gold >= Cost ? true : false;
	}
	else
	{
		return false;
	}
}

void ASunsetPlayerController::ReimburseTowerCost(ATower* Tower)
{
	ASunsetPlayerState* SPlayerState = Cast<ASunsetPlayerState>(PlayerState);
	if (!SPlayerState || !Tower) return;

	SPlayerState->ModifyGold(Tower->Cost);
	SpawningTower->Destroy();
	SpawningTower = nullptr;
}