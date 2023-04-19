// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

class AStar;
UCLASS()
class SWIFTER_API APlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* variables for the random planet generation (based on real scientific data) */
	inline static constexpr float LOWEST_PLANET_MASS_RECORDED = 3.285e23f;
	inline static constexpr float HIGHEST_PLANET_MASS_RECORDED = 1.898e27f;

	inline static constexpr float COLDEST_PLANET_TEMPERATURE_RECORDED = -223.f;
	inline static constexpr float HOTTEST_PLANET_TEMPERATURE_RECORDED = 4300.f;
	
	inline static constexpr double PI_VALUE = 3.1415926535897932384626433832795;
	inline static constexpr float GRAVITATIONAL_CONSTANT = 6.67430e-11f;

	void GenerateName(FString& GivenName) const;
	
	static FString KgToSolarMass(const float& MassInKg);

public:
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

	void Init(AStar* GivenStar);
	void CalculateParams();

	/* The name of this planet */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet Properties")
	FString Name;

	/* The star this planet orbits */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet Properties")
	AStar* Star;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet Properties")
	float Mass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet Properties")
	float SurfaceTemperature;

	/* The 3d mesh that represents this planet */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet Properties", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComp;

	/* The point around this planet rotates, should be set to the star it orbits */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Planet Properties", meta=(AllowPrivateAccess = "true"))
	USceneComponent* PivotPoint;
};
