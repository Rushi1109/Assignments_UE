// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SScrollBox.h"
#include "DataAsset/MeshAssetManager.h"

/**
 * 
 */
class ASSIGNMENT4_API SMeshSelectionScrollBox : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SMeshSelectionScrollBox) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UMeshAssetManager>, InMeshAssetManager)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void LoadAssetInScrollBox();
private:

	TWeakObjectPtr<UMeshAssetManager> MeshAssetManager;
	TSharedPtr<SScrollBox> ScrollBox;
};
