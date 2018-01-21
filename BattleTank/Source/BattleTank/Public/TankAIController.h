// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	


private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	
	ATank* GetPlayerTank() const;
};
