// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	auto ControlledTank = GetPawn();
	if (ensure(ControlledTank))
	{
		auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (ensure(PlayerTank))
		{
			MoveToActor(PlayerTank, AceptanceRadious);

			auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
			if (!ensure(TankAimingComponent)) { return; }

			TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
			// ControlledTank->Fire();
		}
	}
}
