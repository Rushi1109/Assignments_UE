// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "SelectionArea.generated.h"

UENUM()
enum EShapeType : uint8 {
	Spherical,
	Box
};

UCLASS()
class ASSIGNMENT_5_6_API ASelectionArea : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASelectionArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void CreateAreaShape();

	UFUNCTION(BlueprintCallable)
	void GenerateBox(int32 SectionIndex, double DimensionX, double DimensionY, double DimensionZ, double ZOffset = 0.f);

	UFUNCTION(BlueprintCallable)
	void GenerateSphere(int32 SectionIndex, float Radius, int32 RingsCount, int32 PointsCount, double ZOffset = 0.f, float CurveFactor = 1.f);

	void DrawTriangleFromVertex(TArray<int32>& Triangles, int32 Vertex0, int32 Vertex1, int32 Vertex2);

	UPROPERTY()
	TEnumAsByte<EShapeType> ShapeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Mesh")
	UMaterialInterface* TranslucentMaterial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Procedural Mesh")
	UProceduralMeshComponent* ProceduralMeshComponent;
};
