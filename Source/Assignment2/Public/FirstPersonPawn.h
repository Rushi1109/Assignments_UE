// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "InputMappingContext.h"
#include "InputAction.h"

#include "FirstPersonPawn.generated.h"

UCLASS()
class ASSIGNMENT2_API AFirstPersonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFirstPersonPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* CapsuleComponent;

	UInputMappingContext* PawnMappingContext;
	UInputAction* MoveAction;
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditDefaultsOnly)
	float MoveScale;

	void Move(const FInputActionValue& ActionValue);
	void LookAround(const FInputActionValue& ActionValue);
};
