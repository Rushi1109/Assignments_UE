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
	virtual void BeginPlay() override;

	AWallBuilderController();
	virtual void SetupInputComponent() override;

	void LeftClickHandle(const FInputActionValue& ActionValue);
	void RightClickHandle(const FInputActionValue& ActionValue);
	void SelectPreviousWallHandle(const FInputActionValue& ActionValue);
	void SelectNextWallHandle(const FInputActionValue& ActionValue);
	void DestroySplineWallHandle(const FInputActionValue& ActionValue);
	void DeleteLastSplineWallHandle(const FInputActionValue& ActionValue);

	UInputAction* LeftClickAction;
	UInputAction* RightClickAction;
	UInputAction* SelectPreviousWallAction;
	UInputAction* SelectNextWallAction;
	UInputAction* DestroySplineWallAction;
	UInputAction* DeleteLastSplineWallAction;
	UInputMappingContext* MappingContext;

	UPROPERTY(VisibleAnywhere)
	TArray<AWallSpline*> ArrayWallSpline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spline")
	TSubclassOf<AWallSpline> SplineType;

	UPROPERTY()
	int WallIndex;
};
