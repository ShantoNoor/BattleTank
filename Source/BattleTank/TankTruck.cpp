// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTruck.h"

void UTankTruck::SetThrottle(float Throttle)
{
	auto name = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s : Throttle -> %f"), *name, Throttle);

	auto AppliedForce = Throttle * GetForwardVector() * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}