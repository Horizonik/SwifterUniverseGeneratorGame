// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarSystem.generated.h"

class AStar;
class APlanet;
class AGalaxy;
UCLASS()
class SWIFTER_API AStarSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStarSystem();
	void Init(AGalaxy* GivenGalaxy);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const int32 MAX_PLANET_AMOUNT = 10;
	const int32 MIN_PLANET_AMOUNT = 1;
	
	const int32 MIN_DISTANCE_BETWEEN_PLANETS = 250;
	const int32 MAX_DISTANCE_BETWEEN_PLANETS = 600;

	void GenerateName(FString& GivenName) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* The name of this star system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star System Properties")
	FString Name;

	/* The star of this star system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star System Properties")
	AGalaxy* Galaxy;

	/* The star of this star system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star System Properties")
	AStar* Star;

	/* The planets of this star system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star System Properties")
	TArray<APlanet*> Planets;
};
