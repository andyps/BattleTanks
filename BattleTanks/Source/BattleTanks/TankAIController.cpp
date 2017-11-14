// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay - player tank not found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController::BeginPlay - found player tank - %s"), *PlayerTank->GetName());
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) return nullptr;
	return Cast<ATank>(PlayerPawn);
}
