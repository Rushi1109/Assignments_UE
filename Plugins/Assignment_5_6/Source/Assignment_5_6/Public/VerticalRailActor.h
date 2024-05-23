// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "VerticalRailActor.generated.h"

UCLASS()
class ASSIGNMENT_5_6_API AVerticalRailActor : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVerticalRailActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	int AddNewVertex(const FVector& VertexCordinates);

	UFUNCTION(BlueprintCallable)
	int AddUV(const FVector2D& UVCordinates);

	UFUNCTION(BlueprintCallable)
	void DrawTriangleFromVertex(int32 Vertex1, int32 Vertex2, int32 Vertex3);

	UFUNCTION(BlueprintCallable)
	void GenerateCube(const FVector& Dimensions);


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UProceduralMeshComponent* ProceduralMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Mesh")
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Mesh")
	TArray<int32> Triangles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Mesh")
	TArray<FVector2D> UVs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Mesh")
	TArray<FVector> Normals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Mesh")
	TArray<FLinearColor> LinearColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Mesh")
	TArray<FProcMeshTangent> Tangents;
};
