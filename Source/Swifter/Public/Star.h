// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Star.generated.h"

class APlanet;
class AGalaxy;
UCLASS()
class SWIFTER_API AStar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/* variables for the random generation (based on real scientific data) */
	inline static constexpr float LOWEST_STAR_MASS_RECORDED = 1.61103e29f;
	inline static constexpr float HIGHEST_STAR_MASS_RECORDED = 5.271e32f;

	inline static constexpr float COLDEST_STAR_TEMPERATURE_RECORDED = 7000.f;
	inline static constexpr float HOTTEST_STAR_TEMPERATURE_RECORDED = 209726.f;
	
	inline static constexpr double PI_VALUE = 3.1415926535897932384626433832795;
	inline static constexpr float GRAVITATIONAL_CONSTANT = 6.67430e-11f;
	
	float CalculateOrbitalPeriod() const;
	
	float CalculateOrbitalSpeed() const;
	
	float CalculateSurfaceGravity() const;
	
	float EstimateStarDensity() const;
	
	float EstimateStarSize() const;
	
	void GenerateName(FString& GivenName) const;

public:
	UPROPERTY(VisibleAnywhere)
	float Mass;

	UPROPERTY(VisibleAnywhere)
	float SurfaceTemperature;
	
	UPROPERTY(VisibleAnywhere)
	float SemiMajorOrbitAxis;

	UPROPERTY(VisibleAnywhere)
	float OrbitalPeriod;

	UPROPERTY(VisibleAnywhere)
	float OrbitalSpeed;

	UPROPERTY(VisibleAnywhere)
	float SurfaceGravity;

	UPROPERTY(VisibleAnywhere)
	float Density;

	UPROPERTY(VisibleAnywhere)
	float Size;

	UPROPERTY(VisibleAnywhere)
	float Volume;
	
	UPROPERTY(VisibleAnywhere)
	float Radius;

	void Init(AGalaxy* GivenGalaxy);

	/* The name of this planet */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star Properties")
	FString Name;

	/* The star this planet orbits */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star Properties")
	AGalaxy* Galaxy;
	
	/* Planets that orbit this star */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star Properties")
	TArray<APlanet*> OrbitingPlanets;

	/* The 3d mesh that represents this star */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Star Properties", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComp;
};
