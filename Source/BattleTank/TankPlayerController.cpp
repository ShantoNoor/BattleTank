// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Tank = GetControlledTank();
	if (Tank) UE_LOG(LogTemp, Warning, TEXT("Player Tank : %s"), *Tank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		// UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// TODO GetTank aim this point
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLoaction, ViewportSizeY * CrossHairYLoaction);
	// UE_LOG(LogTemp, Warning, TEXT("CrossHairLocation: %s"), *ScreenLocation.ToString());

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *LookDirection.ToString());
		return GetVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	return false;
}

bool ATankPlayerController::GetVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult Hit;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + LookDirection * Reach;
	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECollisionChannel::ECC_Visibility
	)) {
		OutHitLocation = Hit.Location;
		return true;
	}
	OutHitLocation = FVector(0.f);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		OutLookDirection
	);
}
