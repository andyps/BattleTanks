// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"

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
}
