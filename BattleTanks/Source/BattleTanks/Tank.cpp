// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
// #include "TankBarrel.h"
// #include "TankTurret.h"
// #include "TankAimingComponent.h"
// #include "TankMovementComponent.h"
#include "Engine/World.h"
// #include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ Construct"), *TankName);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ BeginPlay Before Super"), *TankName);
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ BeginPlay"), *TankName);

	// TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}
/*
void ATank::Fire()
{
	if (!ensure(Barrel)) return;

	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReloaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATank::Fire!"));

		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}
*/
/*
// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/
/*
void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) return;

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}*/
/*
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}
*/