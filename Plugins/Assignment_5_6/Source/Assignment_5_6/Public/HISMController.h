// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectionArea.h"
#include "GameFramework/PlayerController.h"
#include "MeshGeneratorUI.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "HISMController.generated.h"

/**
 *
 */
UCLASS()
class ASSIGNMENT_5_6_API AHISMController : public APlayerController {
	GENERATED_BODY()
public:
	AHISMController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void HandleLeftClick();

	UFUNCTION()
	void HandleShapeSelectionChange(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void GenerateNewSphere(float InValue);

	UFUNCTION()
	void GenerateNewBox(float InValue);

	UPROPERTY()
	bool bIsAreaSelected;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HISM")
	TSubclassOf<ASelectionArea> SelectionAreaClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HISM")
	ASelectionArea* SelectionAreaShape;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HISM")
	TSubclassOf<UMeshGeneratorUI> MeshGeneratorUIClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "HISM")
	UMeshGeneratorUI* MeshGeneratorUI;

	FVector WorldLocation, WorldDirection;
	FInputModeGameAndUI InputMode;

	UPROPERTY()
	UInputAction* LeftClickAction;

	UPROPERTY()
	UInputMappingContext* MeshGeneratorMappingContext;
};
