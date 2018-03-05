// Fill out your copyright notice in the Description page of Project Settings.

#include "SunsetPawn.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"


// Sets default values
ASunsetPawn::ASunsetPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 800.f;
	CameraArm->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraArm->bDoCollisionTest = false;
	CameraArm->bAbsoluteRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, CameraArm->SocketName);

	

}

// Called when the game starts or when spawned
void ASunsetPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASunsetPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASunsetPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

