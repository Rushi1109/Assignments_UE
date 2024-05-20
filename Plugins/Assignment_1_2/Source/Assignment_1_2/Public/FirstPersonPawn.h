// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PawnAttributeAsset.h"
#include "FirstPersonPawn.generated.h"

UCLASS()
class ASSIGNMENT_1_2_API AFirstPersonPawn : public APawn {
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
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditDefaultsonly)
    UPawnAttributeAsset* PawnAttributeAsset;

    UPROPERTY(EditDefaultsOnly)
    UCameraComponent* Camera;

    UPROPERTY(EditDefaultsOnly)
    UCapsuleComponent* CollisionCapsuleComponent;

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
