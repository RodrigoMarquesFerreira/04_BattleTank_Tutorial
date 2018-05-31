// Copyright UnEpic Studio.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponente = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponente)) {return; }
	FoundAimingComponenet(AimingComponente);
	
}
void ATankPlayerController::OnControlledTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player dead"))
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); // aim towards crosshair
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnControlledTankDeath);
	}
	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponente = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponente)) { return; }
	
	FVector Hitlocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(Hitlocation);
	if (bGotHitLocation) 
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
		return GetLookVectorHitLocation(LookDirection, OutHitlocation);
	}
	return false;
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
