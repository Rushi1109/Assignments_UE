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

void UMeshGeneratorUI::ShowProgressBar() {
	ProgressBar->SetVisibility(ESlateVisibility::Visible);
	HorizontalProgressText->SetVisibility(ESlateVisibility::Visible);
}

void UMeshGeneratorUI::UpdateProgressBar(float InPercent) {
	ProgressBar->SetPercent(InPercent);
	
	FText Percent = FText::AsNumber(FMath::RoundToInt(InPercent * 100));
	FText PercentSymbol = FText::FromString(" %");

	TextProgressPercent->SetText(FText::Format(FText::FromString("{0}{1}"), Percent, PercentSymbol));

	if (InPercent == 1.f) {
		HideProgressBar();
		EnableMeshGenerationButton();
	}
}

void UMeshGeneratorUI::HideProgressBar() {
	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
	HorizontalProgressText->SetVisibility(ESlateVisibility::Hidden);
}

void UMeshGeneratorUI::EnableMeshGenerationButton() {
	GenerateMeshButton->SetIsEnabled(true);
}

void UMeshGeneratorUI::DisableMeshGenerationButton() {
	GenerateMeshButton->SetIsEnabled(false);
}
