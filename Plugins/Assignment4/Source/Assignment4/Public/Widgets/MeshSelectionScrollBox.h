// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SMeshSelectionScrollBox.h"
#include "MeshSelectionScrollBox.generated.h"

DECLARE_DELEGATE_OneParam(FOnMeshAssetReceived, const FMeshData&)
DECLARE_DELEGATE_OneParam(FOnMaterialAssetReceived, const FMaterialData&)
DECLARE_DELEGATE_OneParam(FOnTextureAssetReceived, const FTextureData&)

/**
 * 
 */
UCLASS()
class ASSIGNMENT4_API UMeshSelectionScrollBox : public UWidget {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshAssetManager")
	UMeshAssetManager* MeshAssetManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshAssetManager")
	EAssetType ScrollBoxAssetType;

	FOnMeshAssetReceived OnMeshAssetReceived;
	FOnMaterialAssetReceived OnMaterialAssetReceived;
	FOnTextureAssetReceived OnTextureAssetReceived;

	TSharedPtr<SMeshSelectionScrollBox> GetMeshSelectionScrollBox();

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	const virtual FText GetPaletteCategory() override;
	virtual void SynchronizeProperties() override;
private:
	UFUNCTION()
	void HandleMeshAssetReceived(const FMeshData& MeshData);

	UFUNCTION()
	void HandleMaterialAssetReceived(const FMaterialData& MaterialData);

	UFUNCTION()
	void HandleTextureAssetReceived(const FTextureData& TextureData);
	const FText GetTitleTextFromEnum();



	TSharedPtr<SMeshSelectionScrollBox> MeshSelectionScrollBox;
};
