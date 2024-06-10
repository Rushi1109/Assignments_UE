// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncScatterTask.h"
#include "MeshGenerator.h"

FAsyncScatterTask::FAsyncScatterTask(AMeshGenerator* InMeshGenerator) {
	MeshGenerator = InMeshGenerator;
}

void FAsyncScatterTask::DoWork() {
	if (MeshGenerator) {
		if (UMeshDataAsset* DataAsset = MeshGenerator->DataAsset) {
			TArray<FMeshProps> MeshesData = DataAsset->MeshData;

			for (int i = 0; i < MeshGenerator->GetNumberOfInstances(); ++i) {
				FVector Origin{ MeshGenerator->SelecetionArea->GetActorLocation() };
				FVector Position{};

				if (MeshGenerator->SelecetionArea->ShapeType == EShapeType::Spherical) {
					Position = FindRandomPointInSphere(Origin, MeshGenerator->GetDimensions());
				}
				else {
					Position = FindRandomPointInBox(Origin, MeshGenerator->GetDimensions());
				}

				FTransform MeshTransform{ Position };

				int32 MeshDataIndex = FMath::RandRange(0, MeshesData.Num()-1);
				UStaticMesh* StaticMesh = MeshesData[MeshDataIndex].StaticMesh;

				AsyncTask(ENamedThreads::GameThread, [this, StaticMesh, MeshTransform]() {
					MeshGenerator->AddMeshInstance(StaticMesh, MeshTransform);
				});

				FPlatformProcess::Sleep(0.01f);
			}
		}
	}
}

FVector FAsyncScatterTask::FindRandomPointInBox(FVector Origin, const FVector& ShapeDimensions) {

	Origin.Z += ShapeDimensions.Z / 2;

	FVector BoundingExtent{ ShapeDimensions / 2 };
	FBox BoundingBox{ Origin - BoundingExtent, Origin + BoundingExtent };

	FVector RandomPoint = FMath::RandPointInBox(BoundingBox);

	return RandomPoint;
}

FVector FAsyncScatterTask::FindRandomPointInSphere(FVector Origin, const FVector& ShapeDimensions) {
	float Theta = FMath::RandRange(0.0f, 2 * PI);
	float Phi = FMath::RandRange(0.0f, PI);

	float UFactor = FMath::RandRange(0.0f, 1.0f);
	float Radius = ShapeDimensions.X * FMath::Pow(UFactor, 1.0f / 3.0f);

	float x = Radius * FMath::Sin(Phi) * FMath::Cos(Theta);
	float y = Radius * FMath::Sin(Phi) * FMath::Sin(Theta);
	float z = Radius * FMath::Cos(Phi);

	Origin.Z += ShapeDimensions.Z;
	FVector RandomPoint = Origin + FVector(x, y, z);

	return RandomPoint;
}