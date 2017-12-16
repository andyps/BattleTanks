// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Pawn = GetPawn();
	if (!Pawn) {
		return;
	}
	auto AimingComponent = Pawn->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller can't find aiming component at BeginPlay"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto Pawn = GetPawn();
	if (!Pawn) {
		return;
	}
	auto AimingComponent = Pawn->FindComponentByClass<UTankAimingComponent>();
	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		// Tell controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
	}
		
}

// Get world location of linetrace through crosshair, true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(
		ViewportSizeX * CrossHairXLocation, 
		ViewportSizeY * CrossHairYLocation
	);

	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
		// line-trace along LookDirection
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LineTraceRange * LookDirection);

	bool IsLineTrace = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera
	);
	if (IsLineTrace)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController received Tank too damaged"));
	StartSpectatingOnly();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController SetPawn"));
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		// subscribe
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController subscribe"));
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}
