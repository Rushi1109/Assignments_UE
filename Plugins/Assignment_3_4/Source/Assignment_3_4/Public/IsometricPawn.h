// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IsometricPawn.generated.h"

UCLASS()
class ASSIGNMENT_3_4_API AIsometricPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AIsometricPawn();

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
	UInputMappingContext* IsometricPawnMapping;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UInputAction* CameraLeftRotationAction;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UInputAction* CameraRightRotationAction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UInputAction* ZoomInOutAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RotationSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float TargetRotationYawValue;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UFloatingPawnMovement* FloatingPawnMovement;
 
	UFUNCTION(BlueprintCallable , Category = "Orthographic" , Meta = (AllowPrivateAccess=true))
	void CameraLeftRotation();
 
	UFUNCTION(BlueprintCallable , Category = "Orthographic" , Meta = (AllowPrivateAccess=true))
	void CameraRightRotation();
 
	UFUNCTION(BlueprintCallable , Category = "Orthographic" , Meta = (AllowPrivateAccess = true))
	void CameraZoom(const FInputActionValue& ActionValue); 
};
