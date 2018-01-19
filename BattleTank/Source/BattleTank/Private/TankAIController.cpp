// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlleTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!ControlleTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not possesing a tank"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possesing: %s"), *(ControlleTank->GetName()));
	}
	
	if(!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller fail in find player tank"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possesing: %s"), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{		
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}


ATank * ATankAIController::GetPlayerTank() const
{
		return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


