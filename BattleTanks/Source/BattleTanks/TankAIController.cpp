// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

// Depends on movement component via pathfinding system
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto Pawn = GetPawn();

	if (PlayerTank && Pawn)
	{
		// Move towards the player 
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards the player
		auto AimingComponent = Pawn->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		// Fire if ready
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	}
}
