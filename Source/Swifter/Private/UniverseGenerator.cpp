// Fill out your copyright notice in the Description page of Project Settings.


#include "UniverseGenerator.h"

#include "Galaxy.h"

// Sets default values
AUniverseGenerator::AUniverseGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Padding = 25.f;
	GridHeight = 1.f;
	GridSize = 5;
	SlotSize = 200.f;
}

// Called when the game starts or when spawned
void AUniverseGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	CreateGrid();
	PlacePointsOnGrid();
}

// Called every frame
void AUniverseGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUniverseGenerator::CreateGrid() const
{
	// Generate rows
	for (int32 i = 0; i <= GridSize; i++)
	{
		FVector Start = GetActorLocation() + FVector(i * SlotSize, 0.f, GridHeight);
		FVector End = Start + FVector(0.f, GridSize * SlotSize, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
	}

	// Generate cols
	for (int32 i = 0; i <= GridSize; i++)
	{
		FVector Start = GetActorLocation() + FVector(0.f, i * SlotSize, GridHeight);
		FVector End = Start + FVector(SlotSize * GridSize, 0.f, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
	}
}

FVector AUniverseGenerator::GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight) const
{
	const float RandomX = FMath::RandRange(UpperLeft.X, LowerRight.X);
	const float RandomY = FMath::RandRange(UpperLeft.Y, LowerRight.Y);

	// TODO Add random height fluctuation
	
	return FVector(RandomX, RandomY, GridHeight);
}

void AUniverseGenerator::PlacePointsOnGrid()
{
	// Iterate over each slot in the grid
	for (int32 i = 0; i < GridSize; i++)
	{
		for (int32 j = 0; j < GridSize; j++)
		{
			FVector UpperLeft(i * SlotSize + Padding, j * SlotSize + Padding, GridHeight);
			FVector LowerRight(i * SlotSize + SlotSize - Padding, j * SlotSize + SlotSize - Padding, GridHeight);

			FVector RandomPointInSquare = GetRandomPointInSquare(UpperLeft, LowerRight);
			DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.f, FColor::Red, true);
			DrawDebugCircle(GetWorld(), RandomPointInSquare, Padding, 48, FColor::Red, true, -1.f, 0, 2.5f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f));

			//const float RandomYaw = FMath::RandRange(0.f, 360.f);

			// Spawn a galaxy in the current slot
			UWorld* World = GetWorld();
			FActorSpawnParameters SpawnParams;
			AGalaxy* GalaxyToSpawn = NewObject<AGalaxy>(this, TEXT("GeneratedGalaxy"));

			SpawnParams.Template = GalaxyToSpawn;
			World->SpawnActor<AGalaxy>(GalaxyToSpawn->GetClass(), RandomPointInSquare, FRotator::ZeroRotator, SpawnParams);
		}
	}
}


