// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTruck.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTruck : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);

    UPROPERTY(EditDefaultsOnly) float MaxDrivingForce = 400000.f;
};