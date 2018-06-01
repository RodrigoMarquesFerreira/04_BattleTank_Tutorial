// Copyright UnEpic Studio.

#include "TankTrack.h"
#include "BattleTank.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	
}

void UTankTrack::Drivetrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Drivetrack();
	//ApplySidewaysForce();
	CurrentThrottle = 0.0f;	
}


void UTankTrack::ApplySidewaysForce()
{
	// work-out the required acceleration this frame to correct
	//FVector Velocity = GetComponentVelocity();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//auto SlippageSpeed = FVector::DotProduct(GetRightVector(), FVector(0,0,0));
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAccelaration = (SlippageSpeed / DeltaTime * GetRightVector());

	// calculate and apply sideways for (f = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAccelaration) / 2; // two tracks
	//UE_LOG(LogTemp, Warning, TEXT("Component SlippageSpeed = %f"), SlippageSpeed)
	TankRoot->AddForce(CorrectionForce);

}





