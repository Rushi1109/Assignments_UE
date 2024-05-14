// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/MeshSelectionScrollBox.h"
#include "Widgets/SelectionWidget.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InteractiveArchController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT4_API AInteractiveArchController : public APlayerController {
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void AInteractiveArchController::HandleLeftClick();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<USelectionWidget> SelectionWidget;

private:

	FVector LastHitLocation;
	AActor* CurrentHitActor;


	UInputAction* LeftClickAction;
	UInputMappingContext* InputMappingContext;
};
