// Copyright UnEpic Studio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

//Enum for the aiming State
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	locked
};

// forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

//Hold Barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

	void AimAt(FVector HitLocation);

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	virtual void BeginPlay() override;

	void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection);

	void UTankAimingComponent::MoveTurretTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; // TODO find a ressonable value

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
	
	float ReloadTimeInSeconds = 3.0f;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	double LastFireTime = 0.0f;
};
