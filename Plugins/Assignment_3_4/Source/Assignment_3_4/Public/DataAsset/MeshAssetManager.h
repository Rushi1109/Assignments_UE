// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MeshAssetManager.generated.h"

USTRUCT(BlueprintType)
struct FMeshData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshData")
	FString MeshName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshData")
	UStaticMesh* MeshAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshData")
	UTexture2D* MeshThumbnail;
};

USTRUCT(BlueprintType)
struct FMaterialData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialData")
	FString MaterialName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialData")
	UMaterialInterface* MaterialAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureData")
	UTexture2D* MaterialThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialData")
	FLinearColor MaterialColor;
};

USTRUCT(BlueprintType)
struct FTextureData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureData")
	FString TextureName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureData")
	UTexture* TextureAsset;
};

/**
 * 
 */
UCLASS()
class ASSIGNMENT_3_4_API UMeshAssetManager : public UDataAsset {
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TArray<FMeshData> MeshData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TArray<FMaterialData> MaterialData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	TArray<FTextureData> TextureData;
};
