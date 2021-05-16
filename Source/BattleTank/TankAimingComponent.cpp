// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	LastFireTime = GetWorld()->TimeSeconds;
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if ((GetWorld()->TimeSeconds - LastFireTime) < ReloadTime)
	{
		FiringStates = EFiringStates::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStates = EFiringStates::Aiming;
	}
	else
	{
		FiringStates = EFiringStates::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchSpeed;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	/* bool bHighArc = false, 
	   float CollisionRadius = 0.f, 
	   float OverrideGravityZ = 0, 
	   ESuggestProjVelocityTraceOption::Type TraceOption = ESuggestProjVelocityTraceOption::TraceFullPath, 
	   const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam, 
	   const TArray<AActor*>& ActorsToIgnore = TArray<AActor*>(), 
	   bool bDrawDebug = false 
	*/
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		Barrel,
		OutLaunchSpeed,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchSpeed.GetSafeNormal();
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::SetBarrelAndTurretRef(UTankBarrel* BarreToSet, UTankTurret* TurretToSet)
{
	Barrel = BarreToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards()
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	if (FiringStates != EFiringStates::Reloading)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Firing"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	auto BarrelDirection = Barrel->GetForwardVector().GetSafeNormal();

	if (AimDirection.Equals(BarrelDirection, 0.01)) return true;
	return false;
}
