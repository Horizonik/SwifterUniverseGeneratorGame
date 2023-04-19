// Fill out your copyright notice in the Description page of Project Settings.


#include "Star.h"

#include "Galaxy.h"
#include "Planet.h"

// Sets default values
AStar::AStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the planet mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	if (static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/3D/M_Sphere.M_Sphere'")); MeshAsset.Object)
		MeshComp->SetStaticMesh(MeshAsset.Object);
	
	else
		UE_LOG(LogTemp, Error, TEXT("Couldn't locate star mesh! Verify that the object path is correct!"));
	
	SetRootComponent(MeshComp);
}

// Called when the game starts or when spawned
void AStar::BeginPlay()
{
	Super::BeginPlay();

	// Randomly generate the StarName, Mass and the temperature
	GenerateName(Name);
	Mass = FMath::RandRange(LOWEST_STAR_MASS_RECORDED, HIGHEST_STAR_MASS_RECORDED);
	SurfaceTemperature = FMath::RandRange(COLDEST_STAR_TEMPERATURE_RECORDED, HOTTEST_STAR_TEMPERATURE_RECORDED);
	
	if (Galaxy)
	{
		SemiMajorOrbitAxis = FVector::Distance(GetActorLocation(), Galaxy->GetActorLocation());

		// Orbit around the center of the galaxy
		OrbitalPeriod = CalculateOrbitalPeriod();
		OrbitalSpeed = CalculateOrbitalSpeed();
		
		SurfaceGravity = CalculateSurfaceGravity();
		Size = EstimateStarSize();

		//SetActorScale3D(FVector(Size));

		// Todo set the star to spin around the center of the galaxy
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Galaxy is nullptr. Make sure that a correct Galaxy instance was passed in the parameters!"));
	}
	
}

// Called every frame
void AStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Should be called after creating every new star instance, allows us to pass a star system as a constructor parameter
void AStar::Init(AGalaxy* GivenGalaxy)
{
	Galaxy = GivenGalaxy;
}

// Calculate the orbital period of the star around the center of the galaxy
float AStar::CalculateOrbitalPeriod() const
{
	return 2 * PI_VALUE * sqrt(FMath::Pow(SemiMajorOrbitAxis, 3) / (GRAVITATIONAL_CONSTANT * Mass));
}

// Calculate the orbital speed of the star around the center of the galaxy
float AStar::CalculateOrbitalSpeed() const
{
	return (2 * PI_VALUE * SemiMajorOrbitAxis) / OrbitalPeriod;
}

// Calculate the surface gravity of the star
float AStar::CalculateSurfaceGravity() const
{
	return (GRAVITATIONAL_CONSTANT * Mass) / FMath::Pow(Radius, 2);
}

// Estimate the density of the star (assuming it is a sphere)
float AStar::EstimateStarDensity() const
{
	return Mass / (4.0f / 3.0f * PI_VALUE * FMath::Pow(Radius, 3));
}

// Estimate the size (radius) of the star given its mass and surface gravity
float AStar::EstimateStarSize() const
{
	return FMath::Pow((GRAVITATIONAL_CONSTANT * Mass) / SurfaceGravity, 1.0f / 2.0f);
}

// Randomly creates a name and returns it
void AStar::GenerateName(FString& GivenName) const
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