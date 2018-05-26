// Copyright UnEpic Studio.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

// Responsable for Helpin the player aim.

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000.0f;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333f;


protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponenet(UTankAimingComponent* AimCompRef);

private:


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//Start the ank moving the barrel so that a shot would it where
	//the crosshair intersecs the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitlocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	
};
