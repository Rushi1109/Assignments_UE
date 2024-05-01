// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WallSpline.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "WallBuilderController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT3_API AWallBuilderController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWallBuilderController();
	virtual void SetupInputComponent() override;

	void ClickHandle(const FInputActionValue& ActionValue);

	UInputMappingContext* MappingContext;
	UInputAction* ClickAction;

	UPROPERTY()
	AWallSpline* WallSpline;
};
