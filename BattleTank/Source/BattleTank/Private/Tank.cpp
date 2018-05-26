// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ construct"), *TankName)
	
}


void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (bIsReloaded) 
	{
		/// spawn the projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation("Projectile"),
			Barrel->GetSocketRotation("Projectile")
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); //needed for BP Begin Play to run
}