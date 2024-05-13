// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SMeshSelectionScrollBox.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMeshSelectionScrollBox::Construct(const FArguments& InArgs) {
	
	ScrollBox = SNew(SScrollBox).Orientation(Orient_Horizontal);

	MeshAssetManager = InArgs._InMeshAssetManager;

	ChildSlot
	[
		ScrollBox.ToSharedRef ()
	];
	
}

void SMeshSelectionScrollBox::LoadAssetInScrollBox() {
	ScrollBox->ClearChildren();

	/*if (MeshAssetManager.IsValid()) {
		for (const FMeshData& MeshData : MeshAssetManager->MeshData) {
			if (MeshData.MeshAsset) {
				TSharedPtr<FSlateBrush> ThumbnailBrush = MakeShared<FSlateBrush>();
			}
		}
	}*/
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
