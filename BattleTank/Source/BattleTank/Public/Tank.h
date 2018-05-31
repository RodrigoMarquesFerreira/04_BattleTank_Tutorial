// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100.0f;

	UPROPERTY(VisibleAnyWhere, Category = "Setup")
	int32 CurrentHealth = StartingHealth;
	
};
