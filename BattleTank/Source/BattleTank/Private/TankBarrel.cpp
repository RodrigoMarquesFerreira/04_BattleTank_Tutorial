// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"



void UTankBarrel::Elevate(float DegreesPerSecond) 
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate() called at speed %f"), DegreesPerSecond)
	// move the barrel the right amunt this frame
	// given a max elevation speed, and the frame time
}
