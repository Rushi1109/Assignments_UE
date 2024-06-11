// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectionArea.h"
#include "MeshDataAsset.h"
#include "AsyncScatterTask.h"
#include "MeshGenerator.generated.h"

DECLARE_DELEGATE_OneParam(FOnProgressed, float);

UCLASS()
class ASSIGNMENT_5_6_API AMeshGenerator : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeshGenerator();

	UFUNCTION(BlueprintCallable)
	void AreaParams(ASelectionArea* InSelectionArea, const FVector& InAreaDimensions, int32 InInstanceCount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FinishScatter();

	UFUNCTION(BlueprintCallable)
	void ScatterMeshesInSelectedArea();

	void AddMeshInstance(UStaticMesh* StaticMesh, const FTransform& Transform, UMaterialInstance* Material);

	UPROPERTY(EditDefaultsOnly, Category = "HISM")
	UMeshDataAsset* DataAsset;

	UPROPERTY()
	ASelectionArea* SelecetionArea;

	FOnProgressed OnProgressed;
	
	UFUNCTION(BlueprintPure)
	FVector GetDimensions() const {
		return Dimensions;
	}

	void SetDimensions(const FVector& InDimensions) {
		Dimensions = InDimensions;
	}

	UFUNCTION(BlueprintPure)
	int32 GetNumberOfInstances() const {
		return NumberOfInstances;
	}

	void SetNumberOfInstances(int32 InInstanceCount) {
		NumberOfInstances = InInstanceCount;
	}
private:

	UPROPERTY()
	FVector Dimensions;

	UPROPERTY(EditAnywhere, Category = "HISM")
	int32 NumberOfInstances;

	int32 GeneratedInstances;

	FAsyncTask<FAsyncScatterTask>* AsyncScatterTask;

	UPROPERTY()
	TMap<UStaticMesh*, UHierarchicalInstancedStaticMeshComponent*> HISMComponents;
};
