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

	void HandleLeftClick();
	void HandleTabKey();

	UFUNCTION(BlueprintCallable)
	AArchMeshActor* SpawnMeshFromMeshData();

	UFUNCTION(BlueprintCallable)
	void PopulateMeshData(const FMeshData& Mesh);

	UFUNCTION(BlueprintCallable)
	void PopulateMaterialData(const FMaterialData& Material);

	UFUNCTION(BlueprintCallable)
	void PopulateTextureData(const FTextureData& Texture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<USelectionWidget> SelectionWidget;

private:
	USelectionWidget* Widget;

	FVector LastHitLocation;
	AActor* CurrentHitActor;

	UPROPERTY()
	FMeshData MeshData;

	UPROPERTY()
	FMaterialData MaterialData;

	UPROPERTY()
	FTextureData TextureData;

	FInputModeGameAndUI InputMode;

	bool bIsArchMeshActor;

	UInputAction* LeftClickAction;
	UInputAction* ToggleVisibilityAction;
	UInputMappingContext* InputMappingContext;
};
