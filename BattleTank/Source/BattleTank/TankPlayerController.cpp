// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponente = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponente)) {return; }
	FoundAimingComponenet(AimingComponente);
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); // aim towards crosshair
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponente = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponente)) { return; }
	
	FVector Hitlocation; // Out parameter
	if (GetSightRayHitLocation(Hitlocation)) 
	{	
		AimingComponente->AimAt(Hitlocation);			
	}
}

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
