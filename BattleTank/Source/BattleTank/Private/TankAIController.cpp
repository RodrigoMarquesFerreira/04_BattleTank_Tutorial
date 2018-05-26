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
	// TODO Fix Firing
	//TODO Fire if ready at the player
	//ControlledTank->Fire(); // TODO limit firing rate
	
}





