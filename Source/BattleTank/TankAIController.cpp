// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Tank = GetControlledTank();
	if (Tank) UE_LOG(LogTemp, Warning, TEXT("AI Tank : %s"), *Tank->GetName());

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) { UE_LOG(LogTemp, Warning, TEXT("Found PlayerTank Tank : %s"), *PlayerTank->GetName()); }
	else { UE_LOG(LogTemp, Error, TEXT("Unable to find PlayerTank Tank")); }
}

void ATankAIController::Tick(float DeltaTime)
{
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		auto PlayerTank = GetPlayerTank();
		if (PlayerTank)
		{
			ControlledTank->AimAt(PlayerTank->GetActorLocation());
		}
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
