// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "TopDownPawn.generated.h"

UCLASS()
class ASSIGNMENT_3_4_API ATopDownPawn : public APawn {
    GENERATED_BODY()

   public:
    // Sets default values for this pawn's properties
    ATopDownPawn();

   protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

   public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    void PawnMovement(const FInputActionValue& ActionValue);
    void ScrollWheelMovement(const FInputActionValue& ActionValue);

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    USceneComponent* SceneComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Properties")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Properties")
    UCameraComponent* Camera;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Properties")
    UFloatingPawnMovement* FloatingPawnMovement;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
    UInputMappingContext* PawnMappingContext;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
    UInputAction* MoveAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
    UInputAction* LookAction;
};