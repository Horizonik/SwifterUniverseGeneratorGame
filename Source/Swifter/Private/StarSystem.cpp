// Fill out your copyright notice in the Description page of Project Settings.


#include "StarSystem.h"

#include "Planet.h"
#include "Star.h"

// Sets default values
AStarSystem::AStarSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComp");
}

void AStarSystem::Init(AGalaxy* GivenGalaxy)
{
	Galaxy = GivenGalaxy;

	if (Galaxy)
	{
		// Create star
		Star = NewObject<AStar>(this, FName("GeneratedStar"));
		Star->Init(Galaxy);
		
		// Create planets
		const int PLANET_AMOUNT = FMath::RandRange(MIN_PLANET_AMOUNT, MAX_PLANET_AMOUNT);

		for (int32 i = 0; i < PLANET_AMOUNT; i++)
		{
			APlanet* Planet = NewObject<APlanet>(this, FName("GeneratedPlanet"));
			Planet->Init(Star);
			Planets.Add(Planet);
		}
	
		// Assign planets to Star.orbitingPlanets
		Star->OrbitingPlanets = Planets;
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Galaxy is nullptr. Make sure that a correct Galaxy instance was passed in the parameters!"));
	}
}

// Called when the game starts or when spawned
void AStarSystem::BeginPlay()
{
	Super::BeginPlay();

	// Randomly generate a name for the galaxy
	GenerateName(Name);

	// Spawn all planets and the star
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Template = Star;
	World->SpawnActor<AStar>(Star->GetClass(), GetActorLocation(), GetActorRotation(), SpawnParams);

	// Spawn planet actors and set each of their pivot points to their star
	double PreviousScaleX = Star->MeshComp->GetStaticMesh()->GetBoundingBox().GetExtent().X;
	float XOffset = 0;
	
	for (int i = 0; i < Planets.Num(); i++)
	{
		APlanet* PlanetToSpawn = Planets[i];
	
		// Spawn planet actor
		SpawnParams.Template = PlanetToSpawn;
		World->SpawnActor<APlanet>(PlanetToSpawn->GetClass(), GetActorLocation(), GetActorRotation(), SpawnParams);
		
		const double CurrentScaleX = PlanetToSpawn->MeshComp->GetStaticMesh()->GetBoundingBox().GetExtent().X;
		
		// If this isn't the first iter. Get the scale of the previous planet, else set it as the star's scale
		PreviousScaleX = (i > 0) ? Planets[i-1]->MeshComp->GetStaticMesh()->GetBoundingBox().GetExtent().X: PreviousScaleX;
	
		// + FMath::RandRange(MIN_DISTANCE_BETWEEN_PLANETS, MAX_DISTANCE_BETWEEN_PLANETS);
		XOffset += CurrentScaleX + PreviousScaleX;
		PlanetToSpawn->MeshComp->SetRelativeLocation(FVector(XOffset, 0, 0));
		
		// Randomly rotate each planet
		PlanetToSpawn->SetActorRotation(FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f));
		
		// Initialize the planet's parameters like gravity, mass
		PlanetToSpawn->CalculateParams();
	}
}

// Called every frame
void AStarSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Randomly creates a name and returns it
void AStarSystem::GenerateName(FString& GivenName) const
{
	// GivenName to be generated
	GivenName = "";

	// Chars to make GivenNames from
	FString Letters[2][21] = {
		{"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z"},
		{"a", "e", "i", "o", "u"}
	};

	// Randomly define the length of the GivenName
	const int GivenNameLength = FMath::RandRange(3, 7);

	// Random consonant
	GivenName += Letters[0][FMath::RandRange(0, sizeof Letters[0] / sizeof(FString) - 1)];

	// Random vowel
	GivenName += Letters[1][FMath::RandRange(0, sizeof Letters[1] / sizeof(FString) - 1)];

	// Adds letters until it reaches the max length of the GivenName
	for (int i = 0; i < GivenNameLength; i++)
	{
		const int RowNum = FMath::RandRange(0, 1);

		// Get a random letter out of that row
		GivenName += Letters[RowNum][FMath::RandRange(0, sizeof Letters[RowNum] / sizeof(FString) - 1)];
	}

	// Add a number and a random letter after the GivenName based on a 50% probability
	if (FMath::RandBool())
	{
		GivenName += " +" + FString::FromInt(FMath::RandRange(11, 99));
		GivenName += Letters[0][FMath::RandRange(0, sizeof Letters[0] / sizeof(FString) - 1)];
	}

	// Set first letter to uppercase
	GivenName[0] = toupper(GivenName[0]);
}
