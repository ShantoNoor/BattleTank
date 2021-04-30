// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere) float CrossHairXLoaction = 0.5;
	UPROPERTY(EditAnywhere) float CrossHairYLoaction = 0.25;
	UPROPERTY(EditAnywhere) float Reach = 1000000.f;
};
