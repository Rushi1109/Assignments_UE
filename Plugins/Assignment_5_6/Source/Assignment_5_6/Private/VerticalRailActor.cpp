// Fill out your copyright notice in the Description page of Project Settings.


#include "VerticalRailActor.h"

// Sets default values
AVerticalRailActor::AVerticalRailActor() : CubeDimensions{ 10.0, 10.0, 120.0 } {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->SetupAttachment(SceneRoot);

	GenerateCube(0, CubeDimensions);
	GenerateSphere(1, CubeDimensions.X / 2, 10, 25, CubeDimensions.Z / 2);
}

// Called when the game starts or when spawned
void AVerticalRailActor::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AVerticalRailActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AVerticalRailActor::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

}

void AVerticalRailActor::DrawTriangleFromVertex(TArray<int32>& Triangles, int32 Vertex0, int32 Vertex1, int32 Vertex2) {
	Triangles.Add(Vertex0);
	Triangles.Add(Vertex1);
	Triangles.Add(Vertex2);
}

void AVerticalRailActor::GenerateCube(int32 SectionIndex, const FVector& Dimensions) {
	ProceduralMeshComponent->ClearMeshSection(SectionIndex);

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;

	// Bottom Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 0 - - -
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 1 - + -
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 2 + - -
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 3 + + -

	// Top Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 4 - - +
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 5 - + +
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 6 + - +
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 7 + + +

	// Front Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 8 - - - 0
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 9 - + - 1
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 10 - - + 4
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 11 - + + 5

	// Back Face
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 12 + - - 2
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 13 + + - 3
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 14 + - + 6
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 15 + + + 7

	// Left Face
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 16 + - - 2
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 17 - - - 0
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 18 + - + 6
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 19 - - + 4

	// Right Face
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 20 + + - 3
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 21 - + - 1
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 22 + + + 7
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 23 - + + 5

	// Bottom Face Triangle
	DrawTriangleFromVertex(Triangles, 2, 3, 0);
	DrawTriangleFromVertex(Triangles, 3, 1, 0);

	// Top Face Triangle
	DrawTriangleFromVertex(Triangles, 4, 5, 6);
	DrawTriangleFromVertex(Triangles, 5, 7, 6);

	// Front Face Triangle
	DrawTriangleFromVertex(Triangles, 8, 9, 10);
	DrawTriangleFromVertex(Triangles, 9, 11, 10);

	// Back Face Triangle
	DrawTriangleFromVertex(Triangles, 13, 12, 15);
	DrawTriangleFromVertex(Triangles, 12, 14, 15);

	// Left Face Triangle
	DrawTriangleFromVertex(Triangles, 16, 17, 18);
	DrawTriangleFromVertex(Triangles, 17, 19, 18);

	// Right Face Triangle
	DrawTriangleFromVertex(Triangles, 21, 20, 23);
	DrawTriangleFromVertex(Triangles, 20, 22, 23);

	for (int32 i = 0; i < Vertices.Num(); i += 4) {
		UVs.Add(FVector2D{ 0.0, 1.0 });
		UVs.Add(FVector2D{ 1.0, 1.0 });
		UVs.Add(FVector2D{ 0.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 0.0 });
	}

	for (int32 i = 0; i < Vertices.Num(); ++i) {
		if (i >= 0 && i <= 3) {
			Normals.Add(FVector{ 0.0, 0.0, -1.0 });
		}
		else if (i >= 4 && i <= 7) {
			Normals.Add(FVector{ 0.0, 0.0, 1.0 });
		}
		else if (i >= 8 && i <= 11) {
			Normals.Add(FVector{ -1.0, 0.0, 0.0 });
		}
		else if (i >= 12 && i <= 15) {
			Normals.Add(FVector{ 1.0, 0.0, 0.0 });
		}
		else if (i >= 16 && i <= 19) {
			Normals.Add(FVector{ 0.0, -1.0, 0.0 });
		}
		else if (i >= 20 && i <= 23) {
			Normals.Add(FVector{ 0.0, 1.0, 0.0 });
		}
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateSphere(int32 SectionIndex, float Radius, int32 RingsCount, int32 PointsCount, float ZOffset) {
	ProceduralMeshComponent->ClearMeshSection(SectionIndex);

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

		float V = Theta / PI;

		for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
			float Phi = 2 * PI * PointIndex;
			if (PointsCount > 1) {
				Phi /= (PointsCount - 1);
			}

			float SinPhi = FMath::Sin(Phi);
			float CosPhi = FMath::Cos(Phi);

			float U = Phi / (2 * PI);

			FVector Vertex = FVector{ SinTheta * SinPhi, SinTheta * CosPhi, CosTheta } *Radius;
			Vertex.Z += ZOffset;

			Vertices.Add(Vertex);
			UVs.Add(FVector2D{ U, V });
			Normals.Add(UKismetMathLibrary::GetDirectionUnitVector(FVector{0, 0, ZOffset}, Vertex));

			if (RingIndex < RingsCount - 1 && PointIndex < PointsCount - 1) {
				int32 CurrentRingVertexIndex = RingIndex * PointsCount + PointIndex;
				int32 NextRingVertexIndex = (RingIndex + 1) * PointsCount + PointIndex;

				DrawTriangleFromVertex(Triangles, CurrentRingVertexIndex, NextRingVertexIndex, NextRingVertexIndex + 1);
				DrawTriangleFromVertex(Triangles, NextRingVertexIndex + 1, CurrentRingVertexIndex + 1, CurrentRingVertexIndex);
			}
		}
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}
