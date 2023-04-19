// Fill out your copyright notice in the Description page of Project Settings.


#include "Galaxy.h"

#include "StarSystem.h"

// Sets default values
AGalaxy::AGalaxy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComp");
}

// Called when the game starts or when spawned
void AGalaxy::BeginPlay()
{
	Super::BeginPlay();

	// Randomly generate a name for the galaxy
	GenerateName(Name);

	// Create Star Systems
	const int STAR_SYSTEMS_AMOUNT = FMath::RandRange(MIN_STAR_SYSTEMS_AMOUNT, MAX_STAR_SYSTEMS_AMOUNT);

	// Create and spawn star systems
	UWorld* World = GetWorld();

	for (int32 i = 0; i < STAR_SYSTEMS_AMOUNT; i++)
	{
		AStarSystem* StarSystem = NewObject<AStarSystem>(this, FName("GeneratedStarSystem"));
		StarSystem->Init(this);
		StarSystems.Add(StarSystem);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Template = StarSystem;
		World->SpawnActor<AStarSystem>(StarSystem->GetClass(), GetActorLocation(), GetActorRotation(), SpawnParams);
	}
}

// Called every frame
void AGalaxy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Randomly creates a name and returns it
void AGalaxy::GenerateName(FString& GivenName) const
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
