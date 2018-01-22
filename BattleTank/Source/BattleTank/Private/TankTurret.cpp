// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeRotateSpeed)
{
	RelativeRotateSpeed = FMath::Clamp<float>(RelativeRotateSpeed, -1, +1);
	auto RotationChange = RelativeRotateSpeed * MaxDegreePerSecond * (GetWorld()->DeltaTimeSeconds);
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}


