// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "TankBarrel.generated.h"

/**
 *  #include "Runtime/Engine/Classes/GameFramework/Actor.h"
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max dawnwards speed, and +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = SetUp)
	float MaxDegreePerSecond = 20.0f; 
	
	UPROPERTY(EditDefaultsOnly, Category = SetUp)
	float MaxElevationDegree = 40.0f; 

	UPROPERTY(EditDefaultsOnly, Category = SetUp)
	float MinElevationDegree = 0.0f; 
};
