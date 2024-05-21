// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "OrthographicPawn.generated.h"

UCLASS()
class ASSIGNMENT_3_4_API AOrthographicPawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOrthographicPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite)
	USpringArmComponent* SpringArm;
 
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite)
	UCameraComponent* Camera;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UInputMappingContext* OrthographicPawnMapping;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UInputAction* CameraMovementAction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UInputAction* ZoomInOutAction;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UInputAction* CameraXRotationAction;
 

 
private:
	UFUNCTION(BlueprintCallable, Meta = (AllowPrivateAccess=true))
	void CameraMovement(const FInputActionValue& ActionValue);
 
	UFUNCTION(BlueprintCallable, Meta = (AllowPrivateAccess = true))
	void CameraZoom(const FInputActionValue& ActionValue);
 
	UFUNCTION(BlueprintCallable, Meta = (AllowPrivateAccess = true))
	void RotationX(const FInputActionValue& ActionValue);
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite ,Meta = (AllowPrivateAccess = true))
	UFloatingPawnMovement* FloatingPawnMovement;
};
