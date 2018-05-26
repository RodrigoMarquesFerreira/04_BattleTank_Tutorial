// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
//#include "Public/TankAimingComponent.h"
#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}




void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLauchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLauchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

	//Calculate the outlanchvelocity
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLauchVelocity.GetSafeNormal();
		//move the barrel
		MoveBarrelTowards(AimDirection);
		//move the turret
		MoveTurretTowards(AimDirection);
	
		
	}
	else 
	{
		auto Time = GetWorld()->GetTimeSeconds();
		
	}
	
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("I'm Here"))
	// work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRatator = AimAsRotator - BarrelRotator;
	

		Barrel->Elevate(DeltaRatator.Pitch);
		Turret->Rotate(DeltaRatator.Yaw);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (ensure(Barrel) || ensure(Turret)) { return; }

	// Work-out diferrence between current barrel rotation and aim direction
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}