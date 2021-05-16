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

}

void ATankAIController::Tick(float DeltaTime)
{
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (ensure(ControlledTank))
	{
		auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (ensure(PlayerTank))
		{
			MoveToActor(PlayerTank, AceptanceRadious);
			ControlledTank->AimAt(PlayerTank->GetActorLocation());
			ControlledTank->Fire();
		}
	}
}
