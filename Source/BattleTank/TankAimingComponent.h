// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStates : uint8 
{ 
	Locked, 
	Aiming, 
	Reloading 
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation);
	void MoveBarrelTowards();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 7000.f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStates FiringStates = EFiringStates::Reloading;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelAndTurretRef(UTankBarrel* BarreToSet, UTankTurret* TurretToSet);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3;

	float LastFireTime = 0;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

	bool IsBarrelMoving();

	FVector AimDirection;
};
