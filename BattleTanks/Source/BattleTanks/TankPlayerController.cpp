// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::BeginPlay - no tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::BeginPlay - %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		// TODO Tell controlled tank to aim at this point
	}
		
}

// Get world location of linetrace through crosshair, true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector & HitLocation) const
{
	HitLocation = FVector(1.0);
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(
		ViewportSizeX * CrossHairXLocation, 
		ViewportSizeY * CrossHairYLocation
	);

	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{

	}

	// line-trace along LookDirection
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation;
	bool result = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

	if (result)
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldLocation: %s"), *CameraWorldLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
		return true;
	}
	return result;
}
