// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UniverseGenerator.generated.h"

UCLASS()
class SWIFTER_API AUniverseGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUniverseGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
    void CreateGrid() const;

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight) const;

	void PlacePointsOnGrid();
	
public:
	/* The size each slot in our grid will take */
	UPROPERTY(EditAnywhere, Category = "Universe Generator")
	float SlotSize;

	/* The amount of slots in the generated universe (GridSize powered by 2 = total slots)
	 * Currently the grid can only be in a square ratio (Ex: 1:1, 5:5) */
	UPROPERTY(EditAnywhere, Category = "Universe Generator")
	float GridSize;

	/* Height the grid will be generated at */
	UPROPERTY(EditAnywhere, Category = "Universe Generator")
	float GridHeight;

	/* Padding around slot to prevent collisions.
	 * Should always be set to the same size as the galaxies to prevent them from going out of slot */
	UPROPERTY(VisibleAnywhere, Category = "Universe Generator")
	float Padding;
};
