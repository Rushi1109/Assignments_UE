// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "VerticleRailAsset.h"
#include "FenceMeshActor.generated.h"

USTRUCT(Blueprintable)
struct FFenceProperties {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	float Spacing;
};


UCLASS()
class ASSIGNMENT_5_6_API AFenceMeshActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFenceMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vertical Rail")
	UMaterialInterface* SourceMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Vertical Rail")
	UVerticleRailAsset* VerticleRailAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vertical Rail")
	ERailTopType RailTopType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<UStaticMeshComponent*> RailingStaticMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence Properties")
	FFenceProperties FenceProperties;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	UFUNCTION(BlueprintCallable)
	void GenerateStaticFence();

	UFUNCTION(BlueprintCallable)
	void DestroyStaticFence();

	UFUNCTION(BlueprintCallable)
	void GenerateProceduralFence();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fence")
	UStaticMesh* HorizontalStaticMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Fence")
	TArray<UStaticMeshComponent*> HorizontalStaticMeshes;

	UFUNCTION(BlueprintCallable)
	void GenerateStaticHorizontalMesh();

	UFUNCTION(BlueprintCallable)
	void DestroyStaticHorizontalMesh();

	UFUNCTION(BlueprintCallable)
	void GenerateProceduralHorizontalMesh();
};
