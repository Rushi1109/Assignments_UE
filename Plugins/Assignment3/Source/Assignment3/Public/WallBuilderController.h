// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WallSpline.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "WallBuilderController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(NotificationDelegate, const FString&);

/**
 * 
 */
UCLASS()
class ASSIGNMENT3_API AWallBuilderController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	AWallBuilderController();

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

	NotificationDelegate Notification;

	UPROPERTY(VisibleAnywhere)
	TArray<AWallSpline*> ArrayWallSpline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spline")
	TSubclassOf<AWallSpline> SplineType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spline")
	int32 SplineWallIndex;

	UFUNCTION(BlueprintImplementableEvent)
	void PrintMessageOnViewPort(const FString& Message);
};
