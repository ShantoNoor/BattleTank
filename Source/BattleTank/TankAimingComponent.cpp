// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

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
		FVector AimDirection = OutLaunchSpeed.GetSafeNormal();
		// UE_LOG(LogTemp, Warning, TEXT("AimDirection = %s"), *AimDirection.ToString());

		MoveBarrelTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f : AimSolutionFalse"), GetWorld()->GetTimeSeconds());
	}
}

void UTankAimingComponent::SetBarrelRef(UTankBarrel* BarreToSet)
{
	Barrel = BarreToSet;
}

void UTankAimingComponent::SetTurretRef(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
