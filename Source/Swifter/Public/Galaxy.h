// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Galaxy.generated.h"

class AStarSystem;
UCLASS()
class SWIFTER_API AGalaxy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGalaxy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const int MIN_STAR_SYSTEMS_AMOUNT = 1;
	const int MAX_STAR_SYSTEMS_AMOUNT = 1;

	void GenerateName(FString& GivenName) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* The name of this planet */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Galaxy Properties")
	FString Name;

	/* The star this planet orbits */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Galaxy Properties")
	TArray<AStarSystem*> StarSystems;
};
