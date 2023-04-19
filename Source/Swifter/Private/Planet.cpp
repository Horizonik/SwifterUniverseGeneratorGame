// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

#include "Star.h"

// Sets default values
APlanet::APlanet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the planet mesh
	PivotPoint = CreateDefaultSubobject<USceneComponent>("PivotPoint");
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	if (static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/3D/M_Sphere.M_Sphere'")); MeshAsset.Object)
		MeshComp->SetStaticMesh(MeshAsset.Object);
	
	else
		UE_LOG(LogTemp, Error, TEXT("Couldn't locate planet mesh! Verify that the object path is correct!"));
	
	SetRootComponent(PivotPoint);
	MeshComp->SetupAttachment(PivotPoint);
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (OrbitalPeriod)
	{
		// Rotate around star according to orbital speed
		SetActorRotation(FRotator(0.f, GetActorRotation().Yaw + (OrbitalPeriod * 88), 0.f));
	}
}

// Should be called after creating every new planet instance, allows us to pass a star as a constructor parameter
void APlanet::Init(AStar* GivenStar)
{
	Star = GivenStar;
}

void APlanet::CalculateParams()
{
	// Randomly generate the PlanetName, mass and the temperature
	GenerateName(Name);
	Mass = FMath::RandRange(LOWEST_PLANET_MASS_RECORDED, HIGHEST_PLANET_MASS_RECORDED);
	SurfaceTemperature = FMath::RandRange(COLDEST_PLANET_TEMPERATURE_RECORDED, HOTTEST_PLANET_TEMPERATURE_RECORDED);
	Size = FMath::RandRange(5000,2300000);
	
	if (Star)
	{
		SemiMajorOrbitAxis = FVector::Distance(MeshComp->GetComponentLocation(), Star->MeshComp->GetComponentLocation());
		if (SemiMajorOrbitAxis == 0)
			UE_LOG(LogTemp, Error, TEXT("The planet and its star are overlapping, unable to get correct calculations!"));

		Radius = MeshComp->GetStaticMesh()->GetBoundingBox().GetExtent().X / 2;
		Volume = 4.0 / 3.0 * PI_VALUE * FMath::Pow(Radius, 3);
		Density = Mass / Volume;

		MeshComp->SetAllMassScale(Mass);
		//MeshComp->SetWorldScale3D(FVector(Size / 115000));
		
		OrbitalPeriod = 2 * PI * FMath::Sqrt(FMath::Pow(SemiMajorOrbitAxis, 3) / (GRAVITATIONAL_CONSTANT * Mass));
		OrbitalSpeed = FMath::Sqrt(GRAVITATIONAL_CONSTANT * Mass / SemiMajorOrbitAxis);
		
		SurfaceGravity = GRAVITATIONAL_CONSTANT * Mass / FMath::Pow(Radius, 2);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Star is nullptr. Make sure that a correct Star instance was passed in the parameters!"));
	}
}

// Randomly creates a name and returns it
void APlanet::GenerateName(FString& GivenName) const
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

FString APlanet::KgToSolarMass(const float& MassInKg)
{
	const float MassInSolarMasses = MassInKg / 1.9885e30f;
	return FString::SanitizeFloat(MassInSolarMasses) + "M☉";
}