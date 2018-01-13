// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"



UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	//Start the ank moving the barrel so that a shot would it where
	//the crosshair intersecs the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitlocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
};
