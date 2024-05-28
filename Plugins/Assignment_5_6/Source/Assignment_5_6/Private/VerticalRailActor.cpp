// Fill out your copyright notice in the Description page of Project Settings.


#include "VerticalRailActor.h"

// Sets default values
AVerticalRailActor::AVerticalRailActor() : CubeDimensions{ 10.0, 10.0, 100.0 } {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AVerticalRailActor::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AVerticalRailActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AVerticalRailActor::GenerateVerticalRailActor(const FVector& RailingDimensions) {
	CubeDimensions = RailingDimensions;

	ProceduralMeshComponent->ClearAllMeshSections();

	GenerateCube(0, CubeDimensions);
	GenerateRailingTop(RailingDimensions);
}

void AVerticalRailActor::DrawTriangleFromVertex(TArray<int32>& Triangles, int32 Vertex0, int32 Vertex1, int32 Vertex2) {
	Triangles.Add(Vertex0);
	Triangles.Add(Vertex1);
	Triangles.Add(Vertex2);
}

void AVerticalRailActor::GenerateRailingTop(const FVector& RailDimensions) {
	switch (RailTopType) {
	case ERailTopType::WindsorTurnedCapital:
		break;
	case ERailTopType::RoundTurnedCapital:
		GenerateBellShape(1, RailDimensions.X / 2, RailDimensions.X / 4, RailDimensions.X / 4, 1.0f, 10, 25, (RailDimensions.Z / 2) + (RailDimensions.X / 4));
		GenerateSphere(2, RailDimensions.X / 2, 10, 25, (RailDimensions.Z / 2) + (3 * RailDimensions.X / 4));
		break;
	case ERailTopType::AcornCapital:
		break;
	case ERailTopType::GothicStarTop:
		break;
	case ERailTopType::RoundedOverTop:
		break;
	case ERailTopType::RoundedStarTop:
		break;
	case ERailTopType::PyramidTop:
		break;
	default:
		break;
	}
}

void AVerticalRailActor::GenerateCube(int32 SectionIndex, const FVector& Dimensions) {

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;

	// Front Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 0 - - +
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 1 - - -
	Vertices.Add(FVector{ -Dimensions.X / 2, +Dimensions.Y / 2, -Dimensions.Z / 2 }); // 2 - + -
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 3 - + +

	// Right Face
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 4 - + + 3
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 5 - + - 2
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 6 + + -
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 7 + + +

	// Back Face
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 8 + + + 7
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 9 + + - 6
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 10 + - - 
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 11 + - + 

	// Left Face
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 12 + - + 11
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 13 + - - 10
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 14 - - - 1
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 15 - - + 0

	// Top Face
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 16 + - + 11
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, Dimensions.Z / 2 }); // 17 - - + 0
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 18 - + + 3
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, Dimensions.Z / 2 }); // 19 + + + 7

	// Right Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 20 - - - 1
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, -Dimensions.Z / 2 }); // 21 + - - 10
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 22 + + - 6
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, -Dimensions.Z / 2 }); // 23 - + - 2

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
}

void AVerticalRailActor::GenerateSphere(int32 SectionIndex, float Radius, int32 RingsCount, int32 PointsCount, float ZOffset) {

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

			FVector Vertex = FVector{ SinTheta * SinPhi, SinTheta * CosPhi, CosTheta } *Radius;
			Vertex.Z += ZOffset;
			
			Vertices.Add(Vertex);

			float UChannel = Phi / (2 * PI);
			float VChannel = Theta / PI;
			UVs.Add(FVector2D{ UChannel, VChannel });

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

void AVerticalRailActor::GenerateBellShape(int32 SectionIndex, float BaseRadius, float Height, float RimRadius, float CurvatureFactor, int32 RingsCount, int32 PointsCount, float ZOffset) {

	//Declarations
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	//Vertices
	for (int32 RingIndex = 0; RingIndex < RingsCount; ++RingIndex) {
		float Theta = RingIndex * PI;
		if (RingsCount > 1) {
			Theta /= (RingsCount - 1);
		}

		// Bell profile function for radius interpolation with curvature
		float t = (Theta * 2.0f) / PI;
		float CurrentRadius = FMath::Lerp(BaseRadius, RimRadius, FMath::Sin(t * CurvatureFactor));

		for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
			float Phi = (PointIndex * 2.0f * PI);
			if (PointsCount > 1) {
				Phi /= (PointsCount - 1);
			}

			float SinPhi = FMath::Sin(Phi);
			float CosPhi = FMath::Cos(Phi);

			FVector Vertex = FVector{ CurrentRadius * SinPhi,  CurrentRadius * CosPhi, Height * (t - 1.0f) };
			Vertex.Z += ZOffset;

			Vertices.Add(Vertex);

			float UChannel = Phi / (2 * PI);
			float VChannel = Theta / PI;
			UVs.Add(FVector2D{ UChannel, VChannel });
		}
	}

	//Triangles
	for (int32 RingIndex = 0; RingIndex < RingsCount - 1; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
			int32 BottomLeft = RingIndex * PointsCount + PointIndex;
			int32 BottomRight = BottomLeft + 1;
			int32 TopLeft = BottomLeft + PointsCount;
			int32 TopRight = TopLeft + 1;

			// First triangle
			DrawTriangleFromVertex(Triangles, TopLeft, BottomLeft, BottomRight);
			DrawTriangleFromVertex(Triangles, TopLeft, BottomRight, BottomLeft);

			// Second triangle
			DrawTriangleFromVertex(Triangles, BottomRight, TopRight, TopLeft);
			DrawTriangleFromVertex(Triangles, BottomRight, TopLeft, TopRight);
		}
	}

	for (int32 RingIndex = 0; RingIndex < RingsCount - 1; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
			int32 BottomLeft = RingIndex * PointsCount + PointIndex;
			int32 BottomRight = BottomLeft + 1;
			int32 TopLeft = BottomLeft + PointsCount;
			int32 TopRight = TopLeft + 1;

			auto Normal1 = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[BottomLeft], Vertices[BottomRight]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[BottomLeft], Vertices[TopLeft])).GetSafeNormal();
			auto Normal2 = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[TopRight], Vertices[TopLeft]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[TopRight], Vertices[BottomRight])).GetSafeNormal();

			Normals.Add(Normal1);
			Normals.Add(Normal2);
		}
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}