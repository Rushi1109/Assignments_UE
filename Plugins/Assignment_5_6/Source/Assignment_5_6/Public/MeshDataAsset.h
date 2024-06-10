// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MeshDataAsset.generated.h"

USTRUCT(BlueprintAble)
struct FMeshProps {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	UMaterialInstance* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	float MinScale;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	float MaxScale;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	FRotator MinRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	FRotator MaxRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	float MinDistanceBetweenMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh Data")
	float MaxDistanceBetweenMeshes;
};

/**
 *
 */
UCLASS()
class ASSIGNMENT_5_6_API UMeshDataAsset : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FMeshProps> MeshData;
};
