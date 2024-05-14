// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MeshSelectionScrollBox.h"

TSharedRef<SWidget> UMeshSelectionScrollBox::RebuildWidget() {
	MeshSelectionScrollBox = SNew(SMeshSelectionScrollBox).InMeshAssetManager(MeshAssetManager).InAssetType(ScrollBoxAssetType);
	//MeshSelectionScrollBox->OnAssetThumbnailSelected.BindUFunction(this, "HandleAssetThumbnailSelected");

	return MeshSelectionScrollBox.ToSharedRef();
}

void UMeshSelectionScrollBox::ReleaseSlateResources(bool bReleaseChildren) {
	Super::ReleaseSlateResources(bReleaseChildren);

	MeshSelectionScrollBox.Reset();
}

const FText UMeshSelectionScrollBox::GetPaletteCategory() {
	return FText::FromString("Panel");
}

void UMeshSelectionScrollBox::SynchronizeProperties() {
    Super::SynchronizeProperties();

    if (MeshSelectionScrollBox.IsValid()) {
        MeshSelectionScrollBox->MeshAssetManager = MeshAssetManager;
        MeshSelectionScrollBox->LoadAssetInScrollBox();
    }
}