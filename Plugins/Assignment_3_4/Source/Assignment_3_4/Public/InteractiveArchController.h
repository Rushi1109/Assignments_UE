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
#include "WallSpline.h"
#include "OrthographicPawn.h"
#include "InteractiveArchController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FNotificationDelegate, const FString&);

/**
 * 
 */
UCLASS()
class ASSIGNMENT_3_4_API AInteractiveArchController : public APlayerController {
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
	TSubclassOf<USelectionWidget> SelectionWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* PrintWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> PrintWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* CommandWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widget")
	TSubclassOf<UUserWidget> CommandWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* SwitchModeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widget")
	TSubclassOf<UUserWidget> SwitchModeWidgetClass;

	UFUNCTION(BlueprintImplementableEvent)
    void PrintMessageOnViewPort(const FString& Message);

private:
	USelectionWidget* MeshGeneratorSelectionWidget;

	FVector LastHitLocation;
	AActor* CurrentHitActor;
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY()
	FMeshData MeshData;

	FInputModeGameAndUI InputMode;

	bool bIsArchMeshActor;

	UInputAction* LeftClickAction;
	UInputAction* ToggleVisibilityAction;

	UInputMappingContext* MeshGeneratorMappingContext;

	void SetupMeshGeneratorInput();

	UInputAction* TogglePawnAction;

	UInputMappingContext* SwitchMappingContext;

	void SetupSwitchInput();

	TArray<TSubclassOf<APawn>> PawnReferences;

	int PawnIndex;

	// Wall

	UInputMappingContext* WallGeneratorMappingContext;

	void SetupWallGeneratorInput();

	void LeftClickHandle(const FInputActionValue& ActionValue);
    void RightClickHandle(const FInputActionValue& ActionValue);

    UFUNCTION(BlueprintCallable)
    void SelectPreviousWallHandle(const FInputActionValue& ActionValue);

    UFUNCTION(BlueprintCallable)
    void SelectNextWallHandle(const FInputActionValue& ActionValue);

    UFUNCTION(BlueprintCallable)
    void DestroySplineWallHandle(const FInputActionValue& ActionValue);

    UFUNCTION(BlueprintCallable)
    void DeleteLastSplineWallHandle(const FInputActionValue& ActionValue);

    UFUNCTION(BlueprintCallable)
    void DestroyAllSplineWall();

	FNotificationDelegate Notification;

    UPROPERTY(EditDefaultsOnly)
    TArray<AWallSpline*> ArrayWallSpline;

    UPROPERTY(EditDefaultsOnly, Category = "Spline")
    TSubclassOf<AWallSpline> SplineType;

    UPROPERTY(EditDefaultsOnly, Category = "Spline")
    int32 SplineWallIndex;

	//Toggle Mode
	bool bToggleInputContext;

	UInputMappingContext* CurrentMappingContext;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleMappingContext();

	UFUNCTION(BlueprintImplementableEvent)
	void BindToggleMode();
};
