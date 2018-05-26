// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponente = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(AimingComponente){

		FoundAimingComponenet(AimingComponente);
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming componente at begin player"))
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

		///UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *Hitlocation.ToString())
		GetControlledTank()->AimAt(Hitlocation);
				
	}
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitlocation) const
{
	//find the crosshair position
	int32 ViewportSizeX, ViewporteSizeY;
	GetViewportSize(ViewportSizeX, ViewporteSizeY);
	auto SceenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewporteSizeY * CrosshairYLocation);

	//De-project the crosshair
	FVector LookDirection;
	if (GetLookDirection(SceenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitlocation);

		///UE_LOG(LogTemp, Warning, TEXT(" Camera Look direction: %s"), *GetLoo.ToString())
	}

	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWolrdLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWolrdLocation,
		LookDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
		)) 
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.0, 0.0, 0.0);
	return false;
}
