// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	/*
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay - player tank not found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay - found player tank - %s"), *PlayerTank->GetName());
	}
	*/
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank)
	{
		// Move towards the player 
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim towards the player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		GetControlledTank()->Fire();
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) return nullptr;
	return Cast<ATank>(PlayerPawn);
}
