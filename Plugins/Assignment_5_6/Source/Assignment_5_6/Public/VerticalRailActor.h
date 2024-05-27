// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
	void DrawTriangleFromVertex(TArray<int32>& Triangles, int32 Vertex1, int32 Vertex2, int32 Vertex3);

	void GenerateCube(int32 SectionIndex, const FVector& Dimensions);
	void GenerateSphere(int32 SectionIndex, float Radius, int32 RingsCount, int32 PointsCount, float ZOffset);


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ProceduralMesh")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ProceduralMesh")
	UProceduralMeshComponent* ProceduralMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralMesh")
	FVector CubeDimensions;
};
