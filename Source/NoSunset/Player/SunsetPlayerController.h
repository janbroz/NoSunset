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


	void VerticalMovement(float Amount);
	void HorizontalMovement(float Amount);
	void LeftMousePressed();
	void RightMousePressed();
	void LeftMouseReleased();
	void RightMouseReleased();

	UFUNCTION(BlueprintCallable)
		void ToggleBuilding();
	UFUNCTION(BlueprintCallable)
		void ToggleMainMenu();

public:
	class ASunsetPawn* ThePlayerPawn;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bLeftMousePressed : 1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bRightMousePressed : 1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controller information")
		uint32 bBuilding : 1;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player information")
		class UPlayerHUDWidget* PlayerHUD;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player information")
		TSubclassOf<UPlayerHUDWidget> PlayerHUDClass;
};
