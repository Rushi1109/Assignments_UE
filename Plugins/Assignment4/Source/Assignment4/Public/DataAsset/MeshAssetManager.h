// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MeshAssetManager.generated.h"

USTRUCT(BlueprintType)
struct FMeshData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshData")
	FText MeshName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshData")
	UStaticMesh* MeshAsset;
};

USTRUCT(BlueprintType)
struct FMaterialData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialData")
	FText MaterialName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialData")
	UMaterial* MaterialAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialData")
	float Roughness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialData")
	FLinearColor MaterialColor;
};

USTRUCT(BlueprintType)
struct FTextureData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureData")
	FText TextureName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextureData")
	UTexture* TextureAsset;
};

/**
 * 
 */
UCLASS()
class ASSIGNMENT4_API UMeshAssetManager : public UDataAsset {
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TArray<FMeshData> MeshData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TArray<FMaterialData> MaterialData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	TArray<FTextureData> TextureData;
};
