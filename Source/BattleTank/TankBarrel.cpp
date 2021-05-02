// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// UE_LOG(LogTemp, Warning, TEXT("%f : Elevate = %f"), GetWorld()->GetTimeSeconds(), RelativeSpeed);
	UE_LOG(LogTemp, Warning, TEXT("%f : AimSolutionFalse"), GetWorld()->GetTimeSeconds());

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	RawNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}

