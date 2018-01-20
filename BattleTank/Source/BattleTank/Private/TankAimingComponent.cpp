// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
//#include "Public/TankAimingComponent.h"
#include "BattleTank.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLauchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLauchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

	//Calculate the outlanchvelocity
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLauchVelocity.GetSafeNormal();
		//move the barrel
			

		UE_LOG(LogTemp, Warning, TEXT(" Aiming at %s"), *AimDirection.ToString())
	}
	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRatator = AimAsRotator - BarrelRotator;
	

		Barrel->Elevate(5.0f); // TODO remoe magic number
}