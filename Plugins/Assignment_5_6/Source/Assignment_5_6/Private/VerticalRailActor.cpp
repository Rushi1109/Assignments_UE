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

void AVerticalRailActor::GenerateVerticalRailActor(const FVector& RailDimensions) {
	CubeDimensions = RailDimensions;

	ProceduralMeshComponent->ClearAllMeshSections();

	GenerateCube(0, CubeDimensions);
	GenerateRailingTop(RailDimensions);
}

void AVerticalRailActor::DrawTriangleFromVertex(TArray<int32>& Triangles, int32 Vertex0, int32 Vertex1, int32 Vertex2) {
	Triangles.Add(Vertex0);
	Triangles.Add(Vertex1);
	Triangles.Add(Vertex2);
}

void AVerticalRailActor::GenerateRailingTop(const FVector& RailDimensions) {
	switch (RailTopType) {
	case ERailTopType::WindsorTurnedCapital:
		GenerateCube(1, FVector{ RailDimensions.X, RailDimensions.Y, RailDimensions.X / 4 }, (RailDimensions.Z / 2) + (RailDimensions.X / 8));
		GenerateBellShape(2, RailDimensions.X / 2, RailDimensions.X / 4, RailDimensions.X / 4, 1.0f, 50, 15, (RailDimensions.Z / 2) + (RailDimensions.X / 2));
		GenerateSphere(3, RailDimensions.X / 2, 15, 75, (RailDimensions.Z / 2) + (RailDimensions.X));
		GenerateCone(4, RailDimensions.X / 8, RailDimensions.X / 5, 5, 10, (RailDimensions.Z / 2) + (RailDimensions.X) + (RailDimensions.X / 2));
		break;
	case ERailTopType::RoundTurnedCapital:
		GenerateCube(1, FVector{ RailDimensions.X, RailDimensions.Y, RailDimensions.X / 4 }, (RailDimensions.Z / 2) + (RailDimensions.X / 8));
		GenerateBellShape(2, RailDimensions.X / 2, RailDimensions.X / 4, RailDimensions.X / 4, 1.0f, 10, 25, (RailDimensions.Z / 2) + (RailDimensions.X / 2));
		GenerateSphere(3, RailDimensions.X / 2, 10, 25, (RailDimensions.Z / 2) + (RailDimensions.X));
		break;
	case ERailTopType::AcornCapital:
		GenerateCube(1, FVector{ RailDimensions.X, RailDimensions.Y, RailDimensions.X / 4 }, (RailDimensions.Z / 2) + (RailDimensions.X / 8));
		GenerateBellShape(2, RailDimensions.X / 2, RailDimensions.X / 4, RailDimensions.X / 4, 1.0f, 10, 25, (RailDimensions.Z / 2) + (RailDimensions.X / 2));
		GenerateSphere(3, RailDimensions.X / 2, 10, 25, (RailDimensions.Z / 2) + (RailDimensions.X), 1.5);
		GenerateDonut(4, RailDimensions.X / 2, 1, 10, 50, (RailDimensions.Z / 2) + (RailDimensions.X));
		break;
	case ERailTopType::GothicTop:
		GenerateCube(1, FVector{ 2 * RailDimensions.X / 3, 2 * RailDimensions.Y / 3, RailDimensions.X / 10 }, (RailDimensions.Z / 2) + (RailDimensions.X / 20));
		GenerateCube(2, FVector{ RailDimensions.X, RailDimensions.Y, 2 * RailDimensions.X / 3 }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (RailDimensions.X / 3));
		GeneratePrism(3, FVector{ RailDimensions.X, RailDimensions.Y, RailDimensions.X }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (7 * RailDimensions.X / 6));
		break;
	case ERailTopType::GothicStarTop:
		GenerateCube(1, FVector{ 2 * RailDimensions.X / 3, 2 * RailDimensions.Y / 3, RailDimensions.X / 10 }, (RailDimensions.Z / 2) + (RailDimensions.X / 20));
		GenerateCube(2, FVector{ RailDimensions.X, RailDimensions.Y, 2 * RailDimensions.X / 3 }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (RailDimensions.X / 3));
		GeneratePrism(3, FVector{ RailDimensions.X, RailDimensions.Y, RailDimensions.X }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (7 * RailDimensions.X / 6));
		GenerateSideTriangleLeft(4, FVector{ RailDimensions.X, RailDimensions.Y, RailDimensions.X }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (7 * RailDimensions.X / 6));
		GenerateSideTriangleRight(5, FVector{ RailDimensions.X, RailDimensions.Y, RailDimensions.X }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (7 * RailDimensions.X / 6));
		break;
	case ERailTopType::RoundedOverTop:
		GenerateCube(1, FVector{ (2 * RailDimensions.X) / 3, (2 * RailDimensions.Y) / 3, RailDimensions.X / 10 }, (RailDimensions.Z / 2) + (RailDimensions.X / 20));
		GenerateCube(2, FVector{ RailDimensions.X, RailDimensions.Y, (2 * RailDimensions.X) / 3 }, (RailDimensions.Z / 2) + ((13 * RailDimensions.X) / 30));
		GenerateHorizontalHalfCylinder(3, RailDimensions.X / 2, RailDimensions.Y, 10, 50, FVector{ 0, -(RailDimensions.Y / 2) , (RailDimensions.Z / 2) + ((23 * RailDimensions.X) / 30) });
		break;
	case ERailTopType::RoundedStarTop:
		GenerateCube(1, FVector{ (2 * RailDimensions.X) / 3, (2 * RailDimensions.Y) / 3, RailDimensions.X / 10 }, (RailDimensions.Z / 2) + (RailDimensions.X / 20));
		GenerateCube(2, FVector{ RailDimensions.X, RailDimensions.Y, (2 * RailDimensions.X) / 3 }, (RailDimensions.Z / 2) + ((13 * RailDimensions.X) / 30));
		GenerateHorizontalHalfCylinder(3, RailDimensions.X / 2, RailDimensions.Y, 10, 50, FVector{ 0.0f, -(RailDimensions.Y / 2) , (RailDimensions.Z / 2) + ((23 * RailDimensions.X) / 30) });
		GenerateRoundedStar(4, FVector{ RailDimensions.X , RailDimensions.Y ,  RailDimensions.X / 2 }, 25, FVector{ 0.0f, -(RailDimensions.Y / 2), (RailDimensions.Z / 2) + ((23 * RailDimensions.X) / 30) });
		break;
	case ERailTopType::PyramidTop:
		GenerateCube(1, FVector{ 7 * RailDimensions.X / 10, 7 * RailDimensions.Y / 10, RailDimensions.X / 10 }, (RailDimensions.Z / 2) + (RailDimensions.X / 20));
		GenerateCube(2, FVector{ RailDimensions.X, RailDimensions.Y, 2 * RailDimensions.X / 3 }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (RailDimensions.X / 3));
		GeneratePyramid(3, FVector{ RailDimensions.X, RailDimensions.Y, 2 * RailDimensions.X / 3 }, (RailDimensions.Z / 2) + (RailDimensions.X / 10) + (RailDimensions.X));
		break;
	default:
		break;
	}
}

void AVerticalRailActor::GenerateCube(int32 SectionIndex, const FVector& Dimensions, float ZOffset) {

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;

	// Front Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 0 - - +
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 1 - - -
	Vertices.Add(FVector{ -Dimensions.X / 2, +Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 2 - + -
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 3 - + +

	// Right Face
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 4 - + + 3
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 5 - + - 2
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 6 + + -
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 7 + + +

	// Back Face
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 8 + + + 7
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 9 + + - 6
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 10 + - - 
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 11 + - + 

	// Left Face
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 12 + - + 11
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 13 + - - 10
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 14 - - - 1
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 15 - - + 0

	// Top Face
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 16 + - + 11
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 17 - - + 0
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 18 - + + 3
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 19 + + + 7

	// Bottom Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 20 - - - 1
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 21 + - - 10
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 22 + + - 6
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 23 - + - 2

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

void AVerticalRailActor::GenerateSphere(int32 SectionIndex, float Radius, int32 RingsCount, int32 PointsCount, float ZOffset, float CurveFactor) {

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

void AVerticalRailActor::GeneratePyramid(int32 SectionIndex, const FVector& Dimensions, float ZOffset) {
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	// Bottom Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 0
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 1
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 2
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 3

	// Pyramid Front Side
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 0
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 3
	Vertices.Add(FVector{ 0, 0, ZOffset + Dimensions.Z });

	// Pyramid Right Side
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 3
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 2
	Vertices.Add(FVector{ 0, 0, ZOffset + Dimensions.Z });

	// Pyramid Back Side
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 2
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 1
	Vertices.Add(FVector{ 0, 0, ZOffset + Dimensions.Z });

	// Pyramid Left Side
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 1
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 0
	Vertices.Add(FVector{ 0, 0, ZOffset + Dimensions.Z });

	// Triangles - Bottom
	DrawTriangleFromVertex(Triangles, 0, 1, 2);
	DrawTriangleFromVertex(Triangles, 2, 3, 0);

	// Triangles - 4 Surface
	for (int32 i = 4; i < 16; i += 3) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
	}

	// UVs - Bottom
	UVs.Add(FVector2D{ 0.0, 0.0 });
	UVs.Add(FVector2D{ 0.0, 1.0 });
	UVs.Add(FVector2D{ 1.0, 1.0 });
	UVs.Add(FVector2D{ 1.0, 0.0 });

	// UVs - 4 Surface
	for (int32 i = 4; i < 16; i += 3) {
		UVs.Add(FVector2D{ 0.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 0.0 });
		UVs.Add(FVector2D{ 0.5, 1.0 });
	}

	// Normals - Bottom
	FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[0], Vertices[3]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[0], Vertices[1]));
	Normals.Add(Normal);
	Normals.Add(Normal);
	Normals.Add(Normal);
	Normals.Add(Normal);

	// Normals - 4 Surface
	for (int32 i = 4; i < 16; i += 3) {
		FVector CurrentNormal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i + 1]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i]));
		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateCone(int32 SectionIndex, float Radius, float Length, int32 RingCount, int32 PointsCount, float ZOffset) {

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	// Surface
	for (int32 RingIndex = 0; RingIndex < RingCount; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {

			float Phi = 2 * PI * PointIndex;
			if (PointsCount > 1) {
				Phi /= (PointsCount - 1);
			}
			float SinPhi = FMath::Sin(Phi);
			float CosPhi = FMath::Cos(Phi);

			float DynamicRadius = Radius * ((float)RingIndex / (RingCount - 1));

			FVector Vertex = FVector{ DynamicRadius * SinPhi,  DynamicRadius * CosPhi, Length * (1 - ((float)RingIndex / (RingCount - 1))) };
			Vertex.Z += ZOffset;

			Vertices.Add(Vertex);
			UVs.Add(FVector2D{ Phi / (2 * PI),  (1.0 - ((float)RingIndex / (RingCount - 1))) });

			if (RingIndex < RingCount - 1 && PointIndex < PointsCount - 1) {
				int32 CurrentVertexIndex = RingIndex * PointsCount + PointIndex;
				int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

				DrawTriangleFromVertex(Triangles, CurrentVertexIndex, NextVertexIndex, NextVertexIndex + 1);
				DrawTriangleFromVertex(Triangles, NextVertexIndex + 1, CurrentVertexIndex + 1, CurrentVertexIndex);
			}
		}
	}

	//Normals
	for (int32 RingIndex = 0; RingIndex < RingCount - 1; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
			int32 CurrentVertexIndex = RingIndex * PointsCount + PointIndex;
			int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

			FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[CurrentVertexIndex]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[NextVertexIndex + 1])).GetSafeNormal();
			Normals.Add(Normal);

			if (PointIndex == PointsCount - 2) {
				Normals.Add(Normal);
			}
		}
	}

	// Normals for last ring of cone
	for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
		int32 CurrentVertexIndex = (RingCount - 2) * PointsCount + PointIndex;
		int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[CurrentVertexIndex]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[NextVertexIndex + 1])).GetSafeNormal();
		Normals.Add(Normal);

		if (PointIndex == PointsCount - 2) {
			Normals.Add(Normal);
		}
	}

	//Base Circle
	Vertices.Add(FVector(0.0f, 0.0f, ZOffset));
	UVs.Add(FVector2D(0.5f, 0.5f));

	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = 2 * PI * PointIndex;
		if (PointsCount > 1) {
			Phi /= (PointsCount - 1);
		}
		float X = Radius * FMath::Sin(Phi);
		float Y = Radius * FMath::Cos(Phi);
		float Z = ZOffset;

		Vertices.Add(FVector(X, Y, Z));
		UVs.Add(FVector2D(Y / Radius / 2.0f + 0.5f, X / Radius / 2.0f + 0.5f));
	}

	FVector Normal = FVector::CrossProduct(Vertices[RingCount * PointsCount + 1], Vertices[RingCount * PointsCount + 2]).GetSafeNormal();
	Normals.Add(Normal);

	//Triangles and Normals
	for (int32 i = 1; i <= PointsCount; ++i) {
		if (i < PointsCount) {
			DrawTriangleFromVertex(Triangles, RingCount * PointsCount + i, RingCount * PointsCount, (RingCount * PointsCount + i + 1));
		}
		else {
			DrawTriangleFromVertex(Triangles, RingCount * PointsCount + i, RingCount * PointsCount, (RingCount * PointsCount + 1));
		}
		Normals.Add(Normal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateCylinder(int32 SectionIndex, float Radius, float Length, int32 RingCount, int32 PointsCount, float ZOffset) {

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	for (int32 RingIndex = 0; RingIndex < RingCount; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {

			float Phi = 2 * PI * PointIndex;
			if (PointsCount > 1) {
				Phi /= (PointsCount - 1);
			}
			float SinPhi = FMath::Sin(Phi);
			float CosPhi = FMath::Cos(Phi);

			FVector Vertex = FVector{ Radius * SinPhi,  Radius * CosPhi, Length * (1 - ((float)RingIndex / (RingCount - 1))) };
			Vertex.Z += ZOffset;

			Vertices.Add(Vertex);
			UVs.Add(FVector2D{ Phi / (2 * PI),  (1 - ((float)RingIndex / (RingCount - 1))) });

			if (RingIndex < RingCount - 1 && PointIndex < PointsCount - 1) {
				int32 CurrentVertexIndex = RingIndex * PointsCount + PointIndex;
				int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

				DrawTriangleFromVertex(Triangles, CurrentVertexIndex, NextVertexIndex, NextVertexIndex + 1);
				DrawTriangleFromVertex(Triangles, NextVertexIndex + 1, CurrentVertexIndex + 1, CurrentVertexIndex);
			}
		}
	}

	//Normals
	for (int32 RingIndex = 0; RingIndex < RingCount - 1; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
			int32 CurrentVertexIndex = RingIndex * PointsCount + PointIndex;
			int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

			FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[CurrentVertexIndex]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[NextVertexIndex + 1])).GetSafeNormal();
			Normals.Add(Normal);

			if (PointIndex == PointsCount - 2) {
				Normals.Add(Normal);
			}
		}
	}

	for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
		int32 CurrentVertexIndex = (RingCount - 2) * PointsCount + PointIndex;
		int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[CurrentVertexIndex]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[NextVertexIndex + 1])).GetSafeNormal();
		Normals.Add(Normal);

		if (PointIndex == PointsCount - 2) {
			Normals.Add(Normal);
		}
	}

	//Base Circle
	Vertices.Add(FVector(0.0f, 0.0f, ZOffset));
	UVs.Add(FVector2D(0.5f, 0.5f));

	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = 2 * PI * PointIndex;
		if (PointsCount > 1) {
			Phi /= (PointsCount - 1);
		}
		float X = Radius * FMath::Sin(Phi);
		float Y = Radius * FMath::Cos(Phi);
		float Z = ZOffset;

		Vertices.Add(FVector(X, Y, Z));
		UVs.Add(FVector2D(Y / Radius / 2.0f + 0.5f, X / Radius / 2.0f + 0.5f));
	}

	FVector Normal = FVector::CrossProduct(Vertices[RingCount * PointsCount + 1], Vertices[RingCount * PointsCount + 2]).GetSafeNormal();
	Normals.Add(Normal);

	//Triangles and Normals
	for (int32 i = 1; i <= PointsCount; ++i) {
		if (i < PointsCount) {
			DrawTriangleFromVertex(Triangles, RingCount * PointsCount + i, RingCount * PointsCount, (RingCount * PointsCount + i + 1));
		}
		else {
			DrawTriangleFromVertex(Triangles, RingCount * PointsCount + i, RingCount * PointsCount, (RingCount * PointsCount + 1));
		}
		Normals.Add(Normal);
	}

	//Top Circle
	Vertices.Add(FVector(0.0f, 0.0f, ZOffset + Length));
	UVs.Add(FVector2D(0.5f, 0.5f));

	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = 2 * PI * PointIndex;
		if (PointsCount > 1) {
			Phi /= (PointsCount - 1);
		}
		float X = Radius * FMath::Sin(Phi);
		float Y = Radius * FMath::Cos(Phi);
		float Z = ZOffset + Length;

		Vertices.Add(FVector(X, Y, Z));
		UVs.Add(FVector2D(Y / Radius / 2.0f + 0.5f, X / Radius / 2.0f + 0.5f));
	}

	Normal = FVector::CrossProduct(Vertices[(RingCount + 1) * PointsCount + 3], Vertices[(RingCount + 1) * PointsCount + 2]).GetSafeNormal();
	Normals.Add(Normal);

	//Triangles and Normals
	for (int32 i = 1; i <= PointsCount; ++i) {
		if (i < PointsCount) {
			DrawTriangleFromVertex(Triangles, (RingCount + 1) * PointsCount + 1, (RingCount + 1) * PointsCount + (i + 1), ((RingCount + 1) * PointsCount + i + 2));
		}
		else {
			DrawTriangleFromVertex(Triangles, (RingCount + 1) * PointsCount + 1, (RingCount + 1) * PointsCount + (i + 1), ((RingCount + 1) * PointsCount + 2));
		}
		Normals.Add(Normal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GeneratePrism(int32 SectionIndex, const FVector& Dimensions, float ZOffset) {
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	// Bottom Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 0
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 1
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 2
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 3

	// Right Face
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 });
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 });
	Vertices.Add(FVector{ Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 });
	Vertices.Add(FVector{ -Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 });

	// Left Face
	Vertices.Add(FVector{ -Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 });
	Vertices.Add(FVector{ Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 });
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 });
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 });

	// Front Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 12
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 13
	Vertices.Add(FVector{ -Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 14

	// Back Face
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 15
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 16
	Vertices.Add(FVector{ Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 17

	// Triangles
	// Rectangle Faces
	for (int i = 0; i < 12; i += 4) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
		DrawTriangleFromVertex(Triangles, i + 2, i + 3, i);
	}

	// 2 Triangle
	for (int i = 12; i < 18; i += 3) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
	}

	// UVs
	// Rectangle Faces
	for (int i = 0; i < 12; i += 4) {
		UVs.Add(FVector2D{ 0.0, 1.0 });
		UVs.Add(FVector2D{ 0.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 1.0 });
	}

	// 2 Triangle
	for (int32 i = 12; i < 18; i += 3) {
		UVs.Add(FVector2D{ 0.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 0.0 });
		UVs.Add(FVector2D{ 0.5, 1.0 });
	}

	// Normals
	for (int i = 0; i < 12; i += 4) {
		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 1], Vertices[i + 2]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i], Vertices[i + 1]));

		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
	}

	for (int32 i = 12; i < 18; i += 3) {
		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i + 1]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i]));

		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateSideTriangleLeft(int32 SectionIndex, const FVector& Dimensions, float ZOffset) {
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	// Left Side Face
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 0
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 1
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 2
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 3

	// Top Side Face
	Vertices.Add(FVector{ -Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 4
	Vertices.Add(FVector{ Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 5
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 6
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 7

	// Front Triangle
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 8
	Vertices.Add(FVector{ -Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 9
	Vertices.Add(FVector{ -Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 10

	// Back Triangle
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 11
	Vertices.Add(FVector{ Dimensions.X / 2, -Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 12
	Vertices.Add(FVector{ Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 13

	// Triangles - Rectangle Sides
	for (int32 i = 0; i < 8; i += 4) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
		DrawTriangleFromVertex(Triangles, i + 2, i + 3, i);
	}

	// 2 Triangles
	for (int32 i = 8; i < 14; i += 3) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
	}

	//UVs
	for (int32 i = 0; i < 8; i += 4) {
		UVs.Add(FVector2D{ 0.0, 1.0 });
		UVs.Add(FVector2D{ 0.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 1.0 });
	}


	UVs.Add(FVector2D{ 0.0, 0.0 });
	UVs.Add(FVector2D{ 0.5, 1.0 });
	UVs.Add(FVector2D{ 0.0, 1.0 });
	UVs.Add(FVector2D{ 1.0, 0.0 });
	UVs.Add(FVector2D{ 1.0, 1.0 });
	UVs.Add(FVector2D{ 0.5, 1.0 });

	// Normals
	for (int i = 0; i < 8; i += 4) {
		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 1], Vertices[i + 2]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i], Vertices[i + 1]));

		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
	}

	for (int32 i = 8; i < 14; i += 3) {
		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i + 1]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i]));

		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateSideTriangleRight(int32 SectionIndex, const FVector& Dimensions, float ZOffset) {
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	// Right Side Face
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 0
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 1
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 2
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 3

	// Top Side Face
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 4
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 5
	Vertices.Add(FVector{ Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 6
	Vertices.Add(FVector{ -Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 7

	// Front Triangle
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 8
	Vertices.Add(FVector{ -Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 9
	Vertices.Add(FVector{ -Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 10

	// Back Triangle
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset - Dimensions.Z / 2 }); // 11
	Vertices.Add(FVector{ Dimensions.X / 2, 0, ZOffset + Dimensions.Z / 2 }); // 12
	Vertices.Add(FVector{ Dimensions.X / 2, Dimensions.Y / 2, ZOffset + Dimensions.Z / 2 }); // 13

	// Triangles - Rectangle Sides
	for (int32 i = 0; i < 8; i += 4) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
		DrawTriangleFromVertex(Triangles, i + 2, i + 3, i);
	}

	// 2 Triangles
	for (int32 i = 8; i < 14; i += 3) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
	}

	//UVs
	for (int32 i = 0; i < 8; i += 4) {
		UVs.Add(FVector2D{ 0.0, 1.0 });
		UVs.Add(FVector2D{ 0.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 0.0 });
		UVs.Add(FVector2D{ 1.0, 1.0 });
	}

	// 2 Triangles
	UVs.Add(FVector2D{ 1.0, 0.0 });
	UVs.Add(FVector2D{ 1.0, 1.0 });
	UVs.Add(FVector2D{ 0.5, 1.0 });
	UVs.Add(FVector2D{ 0.0, 0.0 });
	UVs.Add(FVector2D{ 0.5, 1.0 });
	UVs.Add(FVector2D{ 0.0, 1.0 });

	// Normals
	for (int i = 0; i < 8; i += 4) {
		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 1], Vertices[i + 2]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i], Vertices[i + 1]));

		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
	}

	for (int32 i = 8; i < 14; i += 3) {
		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i + 1]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i]));

		Normals.Add(Normal);
		Normals.Add(Normal);
		Normals.Add(Normal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateHorizontalHalfCylinder(int32 SectionIndex, float Radius, float Length, int32 RingCount, int32 PointsCount, FVector Offset) {

	//Declarations
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	//Populating
	for (int32 RingIndex = 0; RingIndex < RingCount; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {

			float Phi = PI * PointIndex;
			if (PointsCount > 1) {
				Phi /= (PointsCount - 1);
			}
			float SinPhi = FMath::Sin(Phi);
			float CosPhi = FMath::Cos(Phi);

			FVector Vertex = FVector{ Radius * CosPhi, Length * (1 - ((float)RingIndex / (RingCount - 1))),  Radius * SinPhi };
			Vertex += Offset;

			Vertices.Add(Vertex);
			UVs.Add(FVector2D{ Phi / (PI),  (1 - ((float)RingIndex / (RingCount - 1))) });

			if (RingIndex < RingCount - 1 && PointIndex < PointsCount - 1) {
				int32 CurrentVertexIndex = RingIndex * PointsCount + PointIndex;
				int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

				DrawTriangleFromVertex(Triangles, CurrentVertexIndex, NextVertexIndex, NextVertexIndex + 1);
				DrawTriangleFromVertex(Triangles, NextVertexIndex + 1, CurrentVertexIndex + 1, CurrentVertexIndex);
			}
		}
	}

	//Normals
	for (int32 RingIndex = 0; RingIndex < RingCount - 1; ++RingIndex) {
		for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
			int32 CurrentVertexIndex = RingIndex * PointsCount + PointIndex;
			int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

			FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[CurrentVertexIndex]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[NextVertexIndex + 1])).GetSafeNormal();
			Normals.Add(Normal);

			if (PointIndex == PointsCount - 2) {
				Normals.Add(Normal);
			}
		}
	}

	for (int32 PointIndex = 0; PointIndex < PointsCount - 1; ++PointIndex) {
		int32 CurrentVertexIndex = (RingCount - 2) * PointsCount + PointIndex;
		int32 NextVertexIndex = CurrentVertexIndex + PointsCount;

		FVector Normal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[CurrentVertexIndex]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[NextVertexIndex], Vertices[NextVertexIndex + 1])).GetSafeNormal();
		Normals.Add(Normal);

		if (PointIndex == PointsCount - 2) {
			Normals.Add(Normal);
		}
	}

	//Base Circle
	Vertices.Add(Offset);
	UVs.Add(FVector2D(0.5f, 0.5f));

	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = PI * PointIndex;
		if (PointsCount > 1) {
			Phi /= (PointsCount - 1);
		}

		FVector Vertex{ Radius * FMath::Cos(Phi), 0, Radius * FMath::Sin(Phi) };
		UVs.Add(FVector2D(Vertex.X / Radius / 2.0f + 0.5f, Vertex.Z / Radius / 2.0f + 0.5f));

		Vertex += Offset;
		Vertices.Add(Vertex);
	}

	FVector Normal = FVector::CrossProduct(Vertices[RingCount * PointsCount + 1], Vertices[RingCount * PointsCount + 2]).GetSafeNormal();
	Normals.Add(Normal);

	//Triangles and Normals
	for (int32 i = 1; i <= PointsCount; ++i) {
		if (i < PointsCount) {
			DrawTriangleFromVertex(Triangles, RingCount * PointsCount + i, RingCount * PointsCount, (RingCount * PointsCount + i + 1));
		}
		else {
			DrawTriangleFromVertex(Triangles, RingCount * PointsCount + i, RingCount * PointsCount, (RingCount * PointsCount + 1));
		}
		Normals.Add(Normal);
	}

	//Top Circle
	Vertices.Add(FVector(Offset.X, Offset.Y + Length, Offset.Z));
	UVs.Add(FVector2D(0.5f, 0.5f));

	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = PI * PointIndex;
		if (PointsCount > 1) {
			Phi /= (PointsCount - 1);
		}

		FVector Vertex{ Radius * FMath::Cos(Phi), Length, Radius * FMath::Sin(Phi) };
		UVs.Add(FVector2D(Vertex.X / Radius / 2.0f + 0.5f, Vertex.Z / Radius / 2.0f + 0.5f));

		Vertex += Offset;
		Vertices.Add(Vertex);
	}

	Normal = FVector::CrossProduct(Vertices[(RingCount + 1) * PointsCount + 3], Vertices[(RingCount + 1) * PointsCount + 2]).GetSafeNormal();
	Normals.Add(Normal);

	//Triangles and Normals
	for (int32 i = 1; i <= PointsCount; ++i) {
		if (i < PointsCount) {
			DrawTriangleFromVertex(Triangles, (RingCount + 1) * PointsCount + 1, (RingCount + 1) * PointsCount + (i + 1), ((RingCount + 1) * PointsCount + i + 2));
		}
		else {
			DrawTriangleFromVertex(Triangles, (RingCount + 1) * PointsCount + 1, (RingCount + 1) * PointsCount + (i + 1), ((RingCount + 1) * PointsCount + 2));
		}
		Normals.Add(Normal);
	}

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateRoundedStar(int32 SectionIndex, const FVector& StarDimensions, int32 PointsCount, FVector Offset) {

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;

	//Faces
	//Vertices
	//Left Face
	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z + StarDimensions.Z }); //0
	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z }); //1
	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y, Offset.Z }); //2
	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y, Offset.Z + StarDimensions.Z }); //3

	//Top Face
	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z + StarDimensions.Z }); //4
	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y, Offset.Z + StarDimensions.Z }); //5
	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y , Offset.Z + StarDimensions.Z }); //6
	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z + StarDimensions.Z }); //7

	//Right Face
	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y, Offset.Z + StarDimensions.Z }); //8
	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y, Offset.Z }); //9
	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z }); //10
	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z + StarDimensions.Z }); //11

	//Triangles
	for (int32 i = 0; i < 12; i += 4) {
		DrawTriangleFromVertex(Triangles, i, i + 1, i + 2);
		DrawTriangleFromVertex(Triangles, i + 2, i + 3, i);
	}

	//Normals
	for (int32 i = 0; i < 12; i += 4) {
		FVector CurrentNormal = FVector::CrossProduct(UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 2], Vertices[i + 1]), UKismetMathLibrary::GetDirectionUnitVector(Vertices[i + 1], Vertices[i]));

		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
		Normals.Add(CurrentNormal);
	}

	//UVs
	for (int32 i = 0; i < 12; i += 4) {
		UVs.Add(FVector2D{ 0.0,0.0 });
		UVs.Add(FVector2D{ 0.0,1.0 });
		UVs.Add(FVector2D{ 1.0,1.0 });
		UVs.Add(FVector2D{ 1.0,0.0 });
	}

	//Base Circle
	float Radius = StarDimensions.X / 2;

	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y, Offset.Z + StarDimensions.Z }); //Right-Point
	UVs.Add(FVector2D(1.0f, 1.0f)); //IndexOffset-1

	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y, Offset.Z + StarDimensions.Z }); //Left-Point
	UVs.Add(FVector2D(0.0f, 1.0f)); //IndexOffset

	int32 IndexOffset = Vertices.Num() - 1;

	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = (PI * PointIndex) / (PointsCount - 1);

		FVector Vertex{ Radius * FMath::Cos(Phi), 0.0f, Radius * FMath::Sin(Phi) };

		UVs.Add(FVector2D(0.5f - (FMath::Cos(Phi) / 2.0f), FMath::Sin(Phi)));

		Vertex += Offset;
		Vertices.Add(Vertex);
	}

	FVector Normal = FVector::CrossProduct(Vertices[IndexOffset + 1], Vertices[IndexOffset + 2]).GetSafeNormal();
	Normals.Add(Normal);
	Normals.Add(Normal);

	//Triangles
	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = (PI * PointIndex) / (PointsCount - 1);

		if (PointIndex < PointsCount) {
			if (Phi <= PI / 2) {
				DrawTriangleFromVertex(Triangles, IndexOffset + PointIndex, IndexOffset + PointIndex + 1, IndexOffset);
			}
			else {
				DrawTriangleFromVertex(Triangles, IndexOffset + PointIndex, IndexOffset + PointIndex + 1, IndexOffset - 1);
			}
		}
	}

	//Normals
	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		Normals.Add(Normal);
	}

	Vertices.Add(FVector{ Offset.X, Offset.Y, Offset.Z + StarDimensions.Z }); //Top-Middle-Point
	UVs.Add(FVector2D(0.5f, 1.0f));
	Normals.Add(Normal);

	Vertices.Add(FVector{ Offset.X, Offset.Y, Offset.Z + Radius }); //Bottom-Middle-Point
	UVs.Add(FVector2D(0.5f, 0.5f));
	Normals.Add(Normal);

	DrawTriangleFromVertex(Triangles, IndexOffset, Vertices.Num() - 1, Vertices.Num() - 2);
	DrawTriangleFromVertex(Triangles, Vertices.Num() - 2, Vertices.Num() - 1, IndexOffset - 1);

	//Top Circle
	Vertices.Add(FVector{ Offset.X - (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z + StarDimensions.Z }); //Right-Point
	UVs.Add(FVector2D(1.0f, 1.0f)); //IndexOffset-1

	Vertices.Add(FVector{ Offset.X + (StarDimensions.X / 2), Offset.Y + StarDimensions.Y, Offset.Z + StarDimensions.Z }); //Left-Point
	UVs.Add(FVector2D(0.0f, 1.0f)); //IndexOffset

	IndexOffset = Vertices.Num() - 1;

	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = (PI * PointIndex) / (PointsCount - 1);

		FVector Vertex{ Radius * FMath::Cos(Phi), StarDimensions.Y, Radius * FMath::Sin(Phi) };

		UVs.Add(FVector2D(0.5f - (FMath::Cos(Phi) / 2.0f), FMath::Sin(Phi)));

		Vertex += Offset;
		Vertices.Add(Vertex);
	}

	Normal = FVector::CrossProduct(Vertices[IndexOffset + 2], Vertices[IndexOffset + 1]).GetSafeNormal();
	Normals.Add(Normal);
	Normals.Add(Normal);

	//Triangles
	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		float Phi = (PI * PointIndex) / (PointsCount - 1);

		if (PointIndex < PointsCount) {
			if (Phi <= PI / 2) {
				DrawTriangleFromVertex(Triangles, IndexOffset + PointIndex + 1, IndexOffset + PointIndex, IndexOffset);
			}
			else {
				DrawTriangleFromVertex(Triangles, IndexOffset + PointIndex + 1, IndexOffset + PointIndex, IndexOffset - 1);
			}
		}
	}

	//Normals
	for (int32 PointIndex = 0; PointIndex < PointsCount; ++PointIndex) {
		Normals.Add(Normal);
	}

	Vertices.Add(FVector{ Offset.X, Offset.Y + StarDimensions.Y, Offset.Z + StarDimensions.Z }); //Top-Middle-Point
	UVs.Add(FVector2D(0.5f, 1.0f));
	Normals.Add(Normal);

	Vertices.Add(FVector{ Offset.X, Offset.Y + StarDimensions.Y, Offset.Z + Radius }); //Bottom-Middle-Point
	UVs.Add(FVector2D(0.5f, 0.5f));
	Normals.Add(Normal);

	DrawTriangleFromVertex(Triangles, Vertices.Num() - 1, IndexOffset, Vertices.Num() - 2);
	DrawTriangleFromVertex(Triangles, Vertices.Num() - 1, Vertices.Num() - 2, IndexOffset - 1);

	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
}

void AVerticalRailActor::GenerateDonut(int32 SectionIndex, float OuterRadius, float InnerRadius, int NumSegments, int NumSides, float ZOffset) {
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;

	// Generate vertices, normals, UVs, and tangents
	for (int32 SegIdx = 0; SegIdx <= NumSegments; SegIdx++) {
		float Theta = 2.0f * PI * SegIdx / NumSegments;
		float CosTheta = FMath::Cos(Theta);
		float SinTheta = FMath::Sin(Theta);

		for (int32 SideIdx = 0; SideIdx < NumSides; SideIdx++) {
			float Phi = 2.0f * PI * SideIdx / NumSides;
			float CosPhi = FMath::Cos(Phi);
			float SinPhi = FMath::Sin(Phi);

			FVector Vertex = FVector((OuterRadius + InnerRadius * CosTheta) * CosPhi, (OuterRadius + InnerRadius * CosTheta) * SinPhi, InnerRadius * SinTheta);
			Vertex.Z += ZOffset;

			Vertices.Add(Vertex);

			FVector Normal = FVector(CosTheta * CosPhi, CosTheta * SinPhi, SinTheta);
			Normals.Add(Normal);

			FVector2D UV = FVector2D((float)SegIdx / NumSegments, (float)SideIdx / NumSides);
			UVs.Add(UV);

			Tangents.Add(FProcMeshTangent(-SinPhi, CosPhi, 0.0f));
		}
	}

	// Generate triangles
	for (int32 SegIdx = 0; SegIdx < NumSegments; SegIdx++) {
		for (int32 SideIdx = 0; SideIdx < NumSides; SideIdx++) {
			int32 NextSideIdx = (SideIdx + 1) % NumSides;

			int32 TopLeft = SegIdx * NumSides + SideIdx;
			int32 TopRight = SegIdx * NumSides + NextSideIdx;
			int32 BottomLeft = (SegIdx + 1) * NumSides + SideIdx;
			int32 BottomRight = (SegIdx + 1) * NumSides + NextSideIdx;

			// Triangle 1
			DrawTriangleFromVertex(Triangles, TopLeft, BottomLeft, BottomRight);

			// Triangle 2
			DrawTriangleFromVertex(Triangles, TopRight, TopLeft,BottomRight);
		}
	}

	// Set the generated data to the procedural mesh component
	ProceduralMeshComponent->CreateMeshSection_LinearColor(SectionIndex++, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>{}, Tangents, true);
}