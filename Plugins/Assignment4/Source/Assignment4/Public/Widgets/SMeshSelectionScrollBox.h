// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SScrollBox.h"
#include "DataAsset/MeshAssetManager.h"
#include "Brushes/SlateColorBrush.h"

UENUM()
enum class EAssetType : uint8 {
	MeshData UMETA(DisplayName = "Mesh Data"),
	MaterialData UMETA(DisplayName = "Material Data"),
	TextureData UMETA(DisplayName = "Texture Data")
};

DECLARE_DELEGATE_OneParam(FOnMeshAssetSelected, const FMeshData&);
DECLARE_DELEGATE_OneParam(FOnMaterialAssetSelected, const FMaterialData&);
DECLARE_DELEGATE_OneParam(FOnTextureAssetSelected, const FTextureData&);

FSlateFontInfo GetFontInfo();
/**
 * 
 */
class ASSIGNMENT4_API SMeshSelectionScrollBox : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SMeshSelectionScrollBox) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UMeshAssetManager>, InMeshAssetManager)
	SLATE_ARGUMENT(EAssetType, InAssetType)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void LoadAssetInScrollBox();

	void LoadMeshData();
	void LoadMaterialData();
	void LoadTextureData();

	EAssetType AssetType;
	TWeakObjectPtr<UMeshAssetManager> MeshAssetManager;
	TSharedPtr<SScrollBox> ScrollBox;

	FOnMeshAssetSelected OnMeshAssetSelected;
	FOnMaterialAssetSelected OnMaterialAssetSelected;
	FOnTextureAssetSelected OnTextureAssetSelected;
};
