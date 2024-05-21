// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/MeshSelectionScrollBox.h"
#include "Widgets/SelectionWidget.h"
#include "ArchMeshActor.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "DataAsset/MeshAssetManager.h"
#include "EnhancedInputSubsystems.h"
#include "IsometricPawn.h"
#include "PerspectivePawn.h"
#include "OrthographicPawn.h"
#include "InteractiveArchController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT4_API AInteractiveArchController : public APlayerController {
	GENERATED_BODY()
	
public:
	AInteractiveArchController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void HandleLeftClick();

	UFUNCTION()
	void HandleTabKey();

	UFUNCTION()
	void HandleTogglePawn();

	UFUNCTION(BlueprintCallable)
	AArchMeshActor* SpawnMeshFromMeshData();

	UFUNCTION(BlueprintCallable)
	void HandleMeshSelection(const FMeshData& Mesh);

	UFUNCTION(BlueprintCallable)
	void HandleMaterialSelection(const FMaterialData& Material);

	UFUNCTION(BlueprintCallable)
	void HandleTextureSelection(const FTextureData& Texture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<USelectionWidget> SelectionWidget;

private:
	USelectionWidget* Widget;

	FVector LastHitLocation;
	AActor* CurrentHitActor;
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY()
	FMeshData MeshData;

	FInputModeGameAndUI InputMode;

	bool bIsArchMeshActor;

	UInputAction* LeftClickAction;
	UInputAction* ToggleVisibilityAction;
	UInputAction* TogglePawnAction;

	UInputMappingContext* MeshGeneratorMappingContext;

	UInputMappingContext* SwitchMappingContext;

	TArray<TSubclassOf<APawn>> PawnReferences;

	int PawnIndex;
};
