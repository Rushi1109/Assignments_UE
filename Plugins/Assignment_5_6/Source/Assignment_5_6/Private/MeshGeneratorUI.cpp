// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshGeneratorUI.h"

void UMeshGeneratorUI::HideBoxFields() {
	TextDimension->SetVisibility(ESlateVisibility::Hidden);
	CubeDimensionX->SetVisibility(ESlateVisibility::Hidden);
	CubeDimensionY->SetVisibility(ESlateVisibility::Hidden);
	CubeDimensionZ->SetVisibility(ESlateVisibility::Hidden);
	ProgressBar->SetVisibility(ESlateVisibility::Hidden);

	TextRadius->SetVisibility(ESlateVisibility::Visible);
	SphericalRadius->SetVisibility(ESlateVisibility::Visible);
}

void UMeshGeneratorUI::HideSphereFields() {
	TextDimension->SetVisibility(ESlateVisibility::Visible);
	CubeDimensionX->SetVisibility(ESlateVisibility::Visible);
	CubeDimensionY->SetVisibility(ESlateVisibility::Visible);
	CubeDimensionZ->SetVisibility(ESlateVisibility::Visible);

	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
	TextRadius->SetVisibility(ESlateVisibility::Hidden);
	SphericalRadius->SetVisibility(ESlateVisibility::Hidden);
}
