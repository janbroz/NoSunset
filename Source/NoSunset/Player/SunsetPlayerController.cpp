// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetPlayerController.h"
#include "Player/SunsetPawn.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Widgets/PlayerHUD/PlayerHUDWidget.h"
#include "Widgets/PlayerHUD/OptionsWidget.h"
#include "Widgets/PlayerHUD/LevelCompletedWidget.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Towers/Tower.h"
#include "Player/SunsetPlayerState.h"
#include "SunsetGameState.h"
#include "SunsetGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Temporal
#include "Gameplaystats/SunsetEffect.h"
#include "Enemies/Minion.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "Runtime/Engine/Classes/Components/InstancedStaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Player/ConstructionGrid.h"

ASunsetPlayerController::ASunsetPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> PlayerHUD_BP(TEXT("/Game/UI/HUD/PlayerHUD_BP.PlayerHUD_BP_C"));
	if (PlayerHUD_BP.Object)
	{
		PlayerHUDClass = PlayerHUD_BP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Options_BP(TEXT("/Game/UI/HUD/OptionsMenu_BP.OptionsMenu_BP_C"));
	if (Options_BP.Object)
	{
		OptionsWidgetClass = Options_BP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Completed_BP(TEXT("/Game/UI/HUD/CompletedLevel_BP.CompletedLevel_BP_C"));
	if (Completed_BP.Object)
	{
		LevelCompletedWidgetClass = Completed_BP.Object;
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
	//InputComponent->BindAction("ToggleBuilding", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::ToggleBuilding);
	InputComponent->BindAction("ToggleMainMenu", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::ToggleMainMenu);
	InputComponent->BindAction("Escape", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::EscapePressed).bExecuteWhenPaused = true;
	InputComponent->BindAction("MultiBuild", EInputEvent::IE_Pressed, this, &ASunsetPlayerController::ShiftBuildPressed);
	InputComponent->BindAction("MultiBuild", EInputEvent::IE_Released, this, &ASunsetPlayerController::ShiftBuildReleased);
	InputComponent->BindAction("Spacebar", EInputEvent::IE_Released, this, &ASunsetPlayerController::DebuggingFunction);
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
			PlayerHUD->UpdatePlayerResources();
		}
	}

	InitializeBuildingGrid();
	InitializeHUDResources();
}

void ASunsetPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsPaused())
	{
		CheckBuilding();
	}
}

void ASunsetPlayerController::InitializeHUDResources()
{
	if (PlayerHUD)
	{
		ASunsetGameState* GState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
		if (GState)
		{
			GState->UpdatePlayersUIEnemies();
			GState->UpdatePlayersUIWave();
		}
	}
}

void ASunsetPlayerController::InitializeBuildingGrid()
{
	TArray<AActor*> Grids;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AConstructionGrid::StaticClass(), Grids);
	for (auto BuildGrid : Grids)
	{
		AConstructionGrid* TmpGrid = Cast<AConstructionGrid>(BuildGrid);
		if (TmpGrid)
		{
			BuildingGrids.Add(TmpGrid);
		}
	}

	for (auto BuildGrid : BuildingGrids) 
	{
		BuildGrid->SetActorHiddenInGame(true);
	}
}

void ASunsetPlayerController::VerticalMovement(float Amount)
{
	if (ThePlayerPawn && Amount != 0.f)
	{
		FVector NewLocation = ThePlayerPawn->GetActorLocation();

		FRotator Rotation = GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		NewLocation += Direction * 15.f * Amount;
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
		FRotator Rotation = GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		NewLocation += Direction * 15.f * Amount;
		ThePlayerPawn->SetActorLocation(NewLocation);
	}
}

void ASunsetPlayerController::EscapePressed()
{
	bShowingOptionsMenu = !bShowingOptionsMenu;

	ASunsetGameState* GState = Cast<ASunsetGameState>(GetWorld()->GetGameState());
	if (!GState) return;


	if (bShowingOptionsMenu)
	{
		SetPause(bShowingOptionsMenu);
		if (OptionsWidgetClass)
		{
			OptionsWidget = CreateWidget<UOptionsWidget>(this, OptionsWidgetClass);
			if (OptionsWidget)
			{
				OptionsWidget->AddToViewport();
			}
		}
	}
	else
	{
		if (OptionsWidget)
		{
			OptionsWidget->RemoveFromParent();
		}
		if (!GState->bRoundIsOver)
		{
			SetPause(bShowingOptionsMenu);
		}	
	}
}

void ASunsetPlayerController::LeftMousePressed()
{
	bLeftMousePressed = true;
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (Hit.bBlockingHit)
	{
		UHierarchicalInstancedStaticMeshComponent* InstancedMesh = Hit.GetActor()->FindComponentByClass<UHierarchicalInstancedStaticMeshComponent>();	
		if (InstancedMesh)
		{
			int32 InstanceIndex = Hit.Item;
			FTransform InstanceTransform;
			InstancedMesh->GetInstanceTransform(InstanceIndex, InstanceTransform, true);
			//UE_LOG(LogTemp, Warning, TEXT("Clickity click: %s"), *InstanceTransform.GetLocation().ToString());
		}
	}
}

void ASunsetPlayerController::RightMousePressed()
{
	//UE_LOG(LogTemp, Warning, TEXT("Right mouse did something"));
	bRightMousePressed = true;
}

void ASunsetPlayerController::LeftMouseReleased()
{
	bLeftMousePressed = false;


	if (bBuilding && SpawningTower && bValidSurfaceForBuilding)
	{
		SpawningTower->SetTowerMode(ETowerMode::Building);
		SpawningTower->SetMaterialMode(EBuildLocation::Working);
		if (bShiftBuilding)
		{
			auto TClass = SpawningTower->GetClass();
			SpawningTower = nullptr;
			SpawnTowerFromClass(TClass);
			return;
		}
		SpawningTower = nullptr;
		ToggleBuilding();
		ClearSelectedTowers();
		return;
	}

	if (!bBuilding)
	{
		ClearSelectedTowers();
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, true, Hit);
		if (Hit.bBlockingHit)
		{
			SelectedActor = Cast<ATower>(Hit.GetActor());
			if (PlayerHUD)
			{
				PlayerHUD->ShowTowerInformation(SelectedActor);
			}

			if (SelectedActor)
			{
				SelectedActor->ToggleRangeIndicator(true);
			}
		}
	}
}

void ASunsetPlayerController::RightMouseReleased()
{
	bRightMousePressed = false;

	if (bBuilding && SpawningTower)
	{
		//ReimburseTowerCost(SpawningTower);
		ToggleBuilding();
	}
	if (SelectedActor)
	{
		SelectedActor->ToggleRangeIndicator(false);
		SelectedActor = nullptr;
	}

	if (PlayerHUD)
	{
		PlayerHUD->ShowTowerInformation(SelectedActor);
	}
}

void ASunsetPlayerController::ToggleBuilding()
{
	bBuilding = !bBuilding;

	if (!bBuilding && SpawningTower)
	{
		ReimburseTowerCost(SpawningTower);
	}
	if (PlayerHUD)
	{
		PlayerHUD->ToggleBuildOptions(bBuilding);
	}
	for (auto BuildGrid : BuildingGrids)
	{
		BuildGrid->SetActorHiddenInGame(!bBuilding);
	}
}

void ASunsetPlayerController::ToggleMainMenu()
{

}

void ASunsetPlayerController::FirstPressed()
{
	if (bBuilding)
	{
		USunsetGameInstance* GameInstance = Cast<USunsetGameInstance>(GetWorld()->GetGameInstance());
		if (!GameInstance)return;

		//auto TowerClass = GameInstance->GetTowerClass(1, )
	}
}

void ASunsetPlayerController::SecondPressed()
{}

void ASunsetPlayerController::ThirdPressed()
{}

void ASunsetPlayerController::ForthPressed()
{}

void ASunsetPlayerController::ShiftBuildPressed()
{
	bShiftBuilding = true;
}

void ASunsetPlayerController::ShiftBuildReleased()
{
	bShiftBuilding = false;
}



void ASunsetPlayerController::CheckBuilding()
{
	if (bBuilding)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_PhysicsBody, true, Hit);
		//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

		FName BuildTag = FName(TEXT("BuildingZone"));

		if (!Hit.bBlockingHit) return;
		FVector SnapLocation = SnapCoordinates(Hit.Location);
		if (SpawningTower)
		{
			SpawningTower->SetActorLocation(SnapLocation);
		}

		if (Hit.bBlockingHit)
		{
			AConstructionGrid* BuildingGrid = Cast<AConstructionGrid>(Hit.GetActor());
			if (BuildingGrid)
			{
				UHierarchicalInstancedStaticMeshComponent* InstancedMesh = Hit.GetActor()->FindComponentByClass<UHierarchicalInstancedStaticMeshComponent>();
				if (InstancedMesh)
				{
					int32 InstanceIndex = Hit.Item;
					FTransform InstanceTransform;
					InstancedMesh->GetInstanceTransform(InstanceIndex, InstanceTransform, true);
					SpawningTower->SetActorLocation(InstanceTransform.GetLocation());
					SpawningTower->SetMaterialMode(EBuildLocation::Right);
				}
				bValidSurfaceForBuilding = true;
			}
			else
			{
				if (SpawningTower)
				{
					SpawningTower->SetMaterialMode(EBuildLocation::Wrong);
				}
				DrawDebugBox(GetWorld(), SnapLocation, FVector(50.f, 50.f, 50.f), FColor::Red, false, 0.03f, 2, 2.f);
				bValidSurfaceForBuilding = false;
			}
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
	//if (!bBuilding) return false;
	ClearSelectedTowers();
	if (!bBuilding)
	{
		ToggleBuilding();
	}
	if (SpawningTower)
	{
		ReimburseTowerCost(SpawningTower);
	}

	TSubclassOf<ATower> TowerClass = ClassToSpawn;
	auto DefaultTower = TowerClass.GetDefaultObject();

	bool bHasTheMoney = DoesPlayerHasTheMoney(TowerClass);
	if (!bHasTheMoney || !DefaultTower) 
	{
		ToggleBuilding();
		return false;
	}

	FActorSpawnParameters FASP;
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit)
	{
		FVector MouseAt = Hit.Location;
		FTransform MouseTransform(FRotator::ZeroRotator, MouseAt, FVector(1.f, 1.f, 1.f));

		SpawningTower = GetWorld()->SpawnActorDeferred<ATower>(TowerClass,  MouseTransform);
	}
	else
	{
		FTransform MouseTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(1.f, 1.f, 1.f));
		SpawningTower = GetWorld()->SpawnActorDeferred<ATower>(TowerClass, MouseTransform);
	}
	if (SpawningTower)
	{
		SpawningTower->SetOwner(this);
		SpawningTower->SetTowerMode(ETowerMode::Placing);
		UGameplayStatics::FinishSpawningActor(SpawningTower, SpawningTower->GetTransform());

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

void ASunsetPlayerController::SellTower(ATower* Tower)
{
	ASunsetPlayerState* SPlayerState = Cast<ASunsetPlayerState>(PlayerState);
	USunsetGameInstance* SGameInstance = Cast<USunsetGameInstance>(GetGameInstance());

	if (!SPlayerState || !Tower || !SGameInstance) return;

	float Penalty = 1.f;
	switch (SGameInstance->GameDifficulty)
	{
	case EDifficultyMode::Easy :
		Penalty = 1.f;
		break;
	case EDifficultyMode::Medium :
		Penalty = 0.8f;
		break;
	case EDifficultyMode::Hard:
		Penalty = 0.5f;
		break;
	default:
		break;
	}

	const float CostAfterPenalty = Tower->Cost * Penalty;
	SPlayerState->ModifyGold(CostAfterPenalty);
	Tower->Destroy();
}

void ASunsetPlayerController::UpdateHUDResources()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdatePlayerResources();
		PlayerHUD->UpdateResourcesPanel();
	}
}

void ASunsetPlayerController::UpdateHUDRemainingLives()
{
	if (PlayerHUD)
	{
	}
}

void ASunsetPlayerController::UpdateHUDCurrentWave(int32 Number)
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateCurrentWave(Number);
	}
}

void ASunsetPlayerController::UpdateHUDEnemiesAlive(int32 Alive, int32 Spawned)
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateEnemiesAlive(Alive, Spawned);
	}
}

void ASunsetPlayerController::ClearSelectedTowers()
{
	if (SelectedActor)
	{
		SelectedActor->ToggleRangeIndicator(false);
	}
	SelectedActor = nullptr;
}

void ASunsetPlayerController::ShowLevelCompletedMenu()
{
	if (LevelCompletedWidgetClass)
	{
		LevelCompletedWidget = CreateWidget<ULevelCompletedWidget>(this, LevelCompletedWidgetClass);
		if (LevelCompletedWidget)
		{
			LevelCompletedWidget->AddToViewport();
		}
	}
}

void ASunsetPlayerController::DebuggingFunction() 
{
	TArray<AActor*> FoundObjects;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMinion::StaticClass(), FoundObjects);
	

	int32 Numba = 0;
	for (TObjectIterator<USunsetEffect> Itr; Itr; ++Itr)
	{
		Numba++;
	}
	UE_LOG(LogTemp, Warning, TEXT("Holi, tenemos cositos aca: %d"), Numba);
}