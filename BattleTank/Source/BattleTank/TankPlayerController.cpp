// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlleTank = GetControlledTank();
	if (!ControlleTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));

	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlleTank -> GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
		// aim towards crosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector Hitlocation; // Out parameter
	if (GetSightRayHitLocation(Hitlocation)) {

		UE_LOG(LogTemp, Warning, TEXT("Hit Loacation: %s"), *Hitlocation.ToString())
		
				//TODO tell controlled tank to aim at this point 
	}
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitlocation) const
{
	OutHitlocation = FVector(1.0);
	return true;
}