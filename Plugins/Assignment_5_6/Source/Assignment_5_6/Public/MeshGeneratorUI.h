// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/ComboBoxString.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/SpinBox.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/ProgressBar.h"
#include "UMG/Public/Components/EditableTextBox.h"
#include "UMG/Public/Components/CanvasPanel.h"
#include "MeshGeneratorUI.generated.h"

/**
 *
 */
UCLASS()
class ASSIGNMENT_5_6_API UMeshGeneratorUI : public UUserWidget {
	GENERATED_BODY()

public:
	void HideBoxFields();
	void HideSphereFields();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* ComboBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextDimension;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USpinBox* SphericalRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USpinBox* CubeDimensionX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USpinBox* CubeDimensionY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USpinBox* CubeDimensionZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* GenerateMeshButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* InstanceCount;
};
