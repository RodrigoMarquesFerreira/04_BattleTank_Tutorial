// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max left speed, and +1 is max right speed
	void Rotate(float RelativeRotateSpeed);

private:
	UPROPERTY(EditAnyWhere, Category = SetUp)
	float MaxDegreePerSecond = 20.0f;


	
	
};
