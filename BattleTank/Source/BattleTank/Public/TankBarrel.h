// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max dawnwards speed, and +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
private:
	
	UPROPERTY(EditAnyWhere, Category = SetUp)
	float MaxDegreePerSecond = 20.0f; 
	
	UPROPERTY(EditAnyWhere, Category = SetUp)
	float MaxElevationDegree = 30.0f; 

	UPROPERTY(EditAnyWhere, Category = SetUp)
	float MinElevationDegree = 0.0f; 
};
