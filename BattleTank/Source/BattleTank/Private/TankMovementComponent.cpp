// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	///auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT(" Intend move forward throw: %f"), Throw)
	
	//TODO prevent double speed
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

