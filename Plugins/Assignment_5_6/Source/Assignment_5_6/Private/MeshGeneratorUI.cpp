// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshGeneratorUI.h"

void UMeshGeneratorUI::HideBoxFields() {
	Box_X->SetVisibility(ESlateVisibility::Hidden);
	Box_Y->SetVisibility(ESlateVisibility::Hidden);
	Box_Z->SetVisibility(ESlateVisibility::Hidden);
	ProgressBar->SetVisibility(ESlateVisibility::Hidden);

	Box_Spherical->SetVisibility(ESlateVisibility::Visible);
}

void UMeshGeneratorUI::HideSphereFields() {
	Box_X->SetVisibility(ESlateVisibility::Visible);
	Box_Y->SetVisibility(ESlateVisibility::Visible);
	Box_Z->SetVisibility(ESlateVisibility::Visible);

	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
	Box_Spherical->SetVisibility(ESlateVisibility::Hidden);
}
