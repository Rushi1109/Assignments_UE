// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionArea.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASelectionArea::ASelectionArea() : ShapeType{ EShapeType::Spherical }, TranslucentMaterial{ nullptr } {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->SetupAttachment(SceneRoot);

	CreateAreaShape();
}

// Called when the game starts or when spawned
void ASelectionArea::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ASelectionArea::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ASelectionArea::CreateAreaShape() {
	ProceduralMeshComponent->ClearAllMeshSections();

	//GenerateBox(0, 100.0, 100.0, 100.0, 50.0);
	GenerateSphere(1, 100, 30, 50, 100);
}

void ASelectionArea::DrawTriangleFromVertex(TArray<int32>& Triangles, int32 Vertex0, int32 Vertex1, int32 Vertex2) {
	Triangles.Add(Vertex0);
	Triangles.Add(Vertex1);
	Triangles.Add(Vertex2);
}

void ASelectionArea::GenerateBox(int32 SectionIndex, double DimensionX, double DimensionY, double DimensionZ, double ZOffset) {
	ProceduralMeshComponent->ClearAllMeshSections();

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;

	// Front Face
	Vertices.Add(FVector{ -DimensionX / 2, -DimensionY / 2, ZOffset + DimensionZ / 2 }); // 0 - - +
	Vertices.Add(FVector{ -DimensionX / 2, -DimensionY / 2, ZOffset - DimensionZ / 2 }); // 1 - - -
	Vertices.Add(FVector{ -DimensionX / 2, +DimensionY / 2, ZOffset - DimensionZ / 2 }); // 2 - + -
	Vertices.Add(FVector{ -DimensionX / 2, DimensionY / 2, ZOffset + DimensionZ / 2 }); // 3 - + +

	// Right Face
	Vertices.Add(FVector{ -DimensionX / 2, DimensionY / 2, ZOffset + DimensionZ / 2 }); // 4 - + + 3
	Vertices.Add(FVector{ -DimensionX / 2, DimensionY / 2, ZOffset - DimensionZ / 2 }); // 5 - + - 2
	Vertices.Add(FVector{ DimensionX / 2, DimensionY / 2, ZOffset - DimensionZ / 2 }); // 6 + + -
	Vertices.Add(FVector{ DimensionX / 2, DimensionY / 2, ZOffset + DimensionZ / 2 }); // 7 + + +

	// Back Face
	Vertices.Add(FVector{ DimensionX / 2, DimensionY / 2, ZOffset + DimensionZ / 2 }); // 8 + + + 7
	Vertices.Add(FVector{ DimensionX / 2, DimensionY / 2, ZOffset - DimensionZ / 2 }); // 9 + + - 6
	Vertices.Add(FVector{ DimensionX / 2, -DimensionY / 2, ZOffset - DimensionZ / 2 }); // 10 + - - 
	Vertices.Add(FVector{ DimensionX / 2, -DimensionY / 2, ZOffset + DimensionZ / 2 }); // 11 + - + 

	// Left Face
	Vertices.Add(FVector{ DimensionX / 2, -DimensionY / 2, ZOffset + DimensionZ / 2 }); // 12 + - + 11
	Vertices.Add(FVector{ DimensionX / 2, -DimensionY / 2, ZOffset - DimensionZ / 2 }); // 13 + - - 10
	Vertices.Add(FVector{ -DimensionX / 2, -DimensionY / 2, ZOffset - DimensionZ / 2 }); // 14 - - - 1
	Vertices.Add(FVector{ -DimensionX / 2, -DimensionY / 2, ZOffset + DimensionZ / 2 }); // 15 - - + 0

	// Top Face
	Vertices.Add(FVector{ DimensionX / 2, -DimensionY / 2, ZOffset + DimensionZ / 2 }); // 16 + - + 11
	Vertices.Add(FVector{ -DimensionX / 2, -DimensionY / 2, ZOffset + DimensionZ / 2 }); // 17 - - + 0
	Vertices.Add(FVector{ -DimensionX / 2, DimensionY / 2, ZOffset + DimensionZ / 2 }); // 18 - + + 3
	Vertices.Add(FVector{ DimensionX / 2, DimensionY / 2, ZOffset + DimensionZ / 2 }); // 19 + + + 7

	// Bottom Face
	Vertices.Add(FVector{ -DimensionX / 2, -DimensionY / 2, ZOffset - DimensionZ / 2 }); // 20 - - - 1
	Vertices.Add(FVector{ DimensionX / 2, -DimensionY / 2, ZOffset - DimensionZ / 2 }); // 21 + - - 10
	Vertices.Add(FVector{ DimensionX / 2, DimensionY / 2, ZOffset - DimensionZ / 2 }); // 22 + + - 6
	Vertices.Add(FVector{ -DimensionX / 2, DimensionY / 2, ZOffset - DimensionZ / 2 }); // 23 - + - 2

	// Triangles
	for (int32 i = 0; i < 24; i += 4) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
		DrawTriangleFromVertex(Triangles, i + 2, i + 3, i);
	}

	// UVs
	for (int32 i = 0; i < Vertices.Num(); i += 4) {
		UVs.Add(FVector2D{ 0.0, 0.0 });
		UVs.Add(FVector2D{ 0.0, 1.0 });
		UVs.Add(FVector2D{ 1.0, 1.0 });
		UVs.Add(FVector2D{ 1.0, 0.0 });
	}

	// Normals
	for (int32 i = 0; i < 24; i += 4) {
		FVector CurrentNormal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i + 1]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 1], Vertices[i]));

		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
	if (TranslucentMaterial) {
		ProceduralMeshComponent->SetMaterial(SectionIndex, TranslucentMaterial);
	}
	ShapeType = EShapeType::Box;
}

void ASelectionArea::GenerateSphere(int32 SectionIndex, float Radius, int32 RingsCount, int32 PointsCount, double ZOffset, float CurveFactor) {
	ProceduralMeshComponent->ClearAllMeshSections();

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;

	for (int32 RingIndex = 0; RingIndex < RingsCount; ++RingIndex) {
		float Theta = PI * RingIndex;
		if (PointsCount > 1) {
			Theta /= (RingsCount - 1);
		}

		float SinTheta = FMath::Sin(Theta);
		float CosTheta = FMath::Cos(Theta);

		for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
			float Phi = 2 * PI * PointIndex;
			if (PointsCount > 1) {
				Phi /= (PointsCount - 1);
			}

			float SinPhi = FMath::Sin(Phi);
			float CosPhi = FMath::Cos(Phi);

			FVector Vertex = FVector{ SinTheta * SinPhi, SinTheta * CosPhi, CosTheta * CurveFactor } *Radius;
			Vertex.Z += ZOffset;

			Vertices.Add(Vertex);

			float UChannel = Phi / (2 * PI);
			float VChannel = Theta / PI;
			UVs.Add(FVector2D{ UChannel, VChannel });

			Normals.Add(UKismetMathLibrary::GetDirectionUnitVector(FVector{ 0, 0, ZOffset }, Vertex));

			if (RingIndex < RingsCount - 1 && PointIndex < PointsCount - 1) {
				int32 CurrentRingVertexIndex = RingIndex * PointsCount + PointIndex;
				int32 NextRingVertexIndex = (RingIndex + 1) * PointsCount + PointIndex;

				DrawTriangleFromVertex(Triangles, CurrentRingVertexIndex, NextRingVertexIndex, NextRingVertexIndex + 1);
				DrawTriangleFromVertex(Triangles, NextRingVertexIndex + 1, CurrentRingVertexIndex + 1, CurrentRingVertexIndex);
			}
		}
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
	if (TranslucentMaterial) {
		ProceduralMeshComponent->SetMaterial(SectionIndex, TranslucentMaterial);
	}
	ShapeType = EShapeType::Spherical;
}