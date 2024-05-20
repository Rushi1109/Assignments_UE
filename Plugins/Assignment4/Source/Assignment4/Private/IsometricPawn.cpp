// Fill out your copyright notice in the Description page of Project Settings.


#include "IsometricPawn.h"

// Sets default values
AIsometricPawn::AIsometricPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIsometricPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIsometricPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIsometricPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

