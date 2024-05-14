// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SMeshSelectionScrollBox.h"
#include "MeshSelectionScrollBox.generated.h"


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
	TEnumAsByte<EAssetType> ScrollBoxAssetType;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	const virtual FText GetPaletteCategory() override;
	virtual void SynchronizeProperties() override;
private:
	TSharedPtr<SMeshSelectionScrollBox> MeshSelectionScrollBox;
};
