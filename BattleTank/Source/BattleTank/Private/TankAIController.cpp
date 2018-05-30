// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	// Aim towards the player
	auto AimingComponente = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponente)) { return; }
	AimingComponente->AimAt(PlayerTank->GetActorLocation());
	// if aim equal lock 
	if (AimingComponente->GetFiringState() == EFiringState::locked)
	{
		AimingComponente->Fire(); // TODO limit firing rate
	}
}





