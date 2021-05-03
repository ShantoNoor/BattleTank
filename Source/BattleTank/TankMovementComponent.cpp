// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTruck.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	// UE_LOG(LogTemp, Warning, TEXT("%f : IntendToMove -> %f"), GetWorld()->GetTimeSeconds(), Throw);
	LeftTruck->SetThrottle(Throw);
	RightTruck->SetThrottle(Throw);
}

void UTankMovementComponent::SetTracks(UTankTruck* LeftTruckToSet, UTankTruck* RightTruckToSet)
{
	LeftTruck = LeftTruckToSet;
	RightTruck = RightTruckToSet;
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTruck->SetThrottle(Throw);
	RightTruck->SetThrottle(-Throw);
}

