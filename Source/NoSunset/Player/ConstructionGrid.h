// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructionGrid.generated.h"

UCLASS()
class NOSUNSET_API AConstructionGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConstructionGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GridWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GridHeight;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class UHierarchicalInstancedStaticMeshComponent* InstancedMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* SceneComponent;
};
