// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SunsetPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NOSUNSET_API ASunsetPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASunsetPlayerController();
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void VerticalMovement(float Amount);
	void HorizontalMovement(float Amount);
	void LeftMousePressed();
	void RightMousePressed();
	void LeftMouseReleased();
	void RightMouseReleased();
	void EscapePressed();
	void UpdateHUDResources();

	UFUNCTION(BlueprintCallable)
		void FirstPressed();
	UFUNCTION(BlueprintCallable)
		void SecondPressed();
	UFUNCTION(BlueprintCallable)
		void ThirdPressed();
	UFUNCTION(BlueprintCallable)
		void ForthPressed();

	UFUNCTION(BlueprintCallable)
		void ToggleBuilding();
	UFUNCTION(BlueprintCallable)
		void ToggleMainMenu();
	UFUNCTION(BlueprintCallable)
		void CheckBuilding();
	UFUNCTION(BlueprintCallable)
		bool SpawnTowerFromClass(UClass* ClassToSpawn);
	UFUNCTION(BlueprintCallable)
		FVector SnapCoordinates(FVector InitialCoords);
	UFUNCTION(BlueprintCallable)
		bool DoesPlayerHasTheMoney(TSubclassOf<class ATower> ClassToBuild);
	UFUNCTION(BlueprintCallable)
		void ReimburseTowerCost(class ATower* Tower);
public:
	class ASunsetPawn* ThePlayerPawn;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bLeftMousePressed : 1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bRightMousePressed : 1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bBuilding : 1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bValidSurfaceForBuilding : 1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bShowingOptionsMenu : 1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		class ATower* SpawningTower;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player information")
		class UPlayerHUDWidget* PlayerHUD;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player information")
		TSubclassOf<UPlayerHUDWidget> PlayerHUDClass;
};
