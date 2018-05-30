// Copyright UnEpic Studio.


#include "TankAimingComponent.h"
#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
		PrimaryComponentTick.bCanEverTick = true;

	// ...
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState ;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	} 
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::locked;
	}

}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimAt(FVector HitLocation)
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
		 AimDirection = OutLauchVelocity.GetSafeNormal();
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

void UTankAimingComponent::Fire()
{
	//if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	//bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (FiringState == EFiringState::locked)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		/// spawn the projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation("Projectile"),
			Barrel->GetSocketRotation("Projectile")
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRatator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRatator.Pitch);
	if (FMath::Abs(DeltaRatator.Yaw) < 180.0f) 
	{
		Turret->Rotate(DeltaRatator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRatator.Yaw);
	}
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

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.1f);
}
