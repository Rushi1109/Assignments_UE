// Fill out your copyright notice in the Description page of Project Settings.


#include "FenceMeshActor.h"

// Sets default values
AFenceMeshActor::AFenceMeshActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("FenceMeshSplineComponent"));
	SplineComponent->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AFenceMeshActor::BeginPlay() {
	Super::BeginPlay();

	DestroyStaticFence();

	GenerateProceduralFence();
}

// Called every frame
void AFenceMeshActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AFenceMeshActor::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	DestroyStaticFence();

	GenerateStaticFence();
}

void AFenceMeshActor::GenerateStaticFence() {
	int32 SplinePoints = SplineComponent->GetNumberOfSplinePoints();

	float SplineLength = SplineComponent->GetDistanceAlongSplineAtSplinePoint(SplinePoints - 1);

	for (int32 i = 0; i < SplinePoints; ++i) {
		SplineComponent->SetSplinePointType(i, ESplinePointType::Linear);
	}

	float TotalSpacing = FenceProperties.Length + FenceProperties.Spacing;
	float DistanceCovered{ FenceProperties.Length / 2 };

	while (DistanceCovered + FenceProperties.Length <= SplineLength) {
		FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(DistanceCovered, ESplineCoordinateSpace::Local);
		FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(DistanceCovered, ESplineCoordinateSpace::Local);
		Location.Z += FenceProperties.Height / 2;

		UStaticMeshComponent* RailingStaticMeshComponent = NewObject<UStaticMeshComponent>(this);
		RailingStaticMeshComponent->RegisterComponent();
		RailingStaticMeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

		if (RailingStaticMesh) {
			RailingStaticMeshComponent->SetStaticMesh(RailingStaticMesh);
		}

		RailingStaticMeshComponent->SetRelativeLocationAndRotation(Location, Rotation);
		RailingStaticMeshComponent->SetWorldScale3D(FVector{ FenceProperties.Length / 10, FenceProperties.Width / 10, FenceProperties.Height / 100 });

		RailingStaticMeshes.Add(RailingStaticMeshComponent);

		DistanceCovered += TotalSpacing;
	}
	GenerateStaticHorizontalMesh();
}

void AFenceMeshActor::DestroyStaticFence() {
	for (int32 i = 0; i < RailingStaticMeshes.Num(); ++i) {
		if (RailingStaticMeshes[i]) {
			RailingStaticMeshes[i]->DestroyComponent();
			RailingStaticMeshes[i] = nullptr;
		}
	}

	RailingStaticMeshes.Empty();

	DestroyStaticHorizontalMesh();
}

void AFenceMeshActor::GenerateProceduralFence() {
	int32 SplinePointsCount = SplineComponent->GetNumberOfSplinePoints();
	float SplineLength = SplineComponent->GetDistanceAlongSplineAtSplinePoint(SplinePointsCount - 1);

	float TotalSpacing = FenceProperties.Length + FenceProperties.Spacing;
	float DistanceCovered{ 0.0f };

	while (DistanceCovered + FenceProperties.Length <= SplineLength) {
		FVector StartLocation = SplineComponent->GetLocationAtDistanceAlongSpline(DistanceCovered, ESplineCoordinateSpace::World);
		FRotator StartRotation = SplineComponent->GetRotationAtDistanceAlongSpline(DistanceCovered, ESplineCoordinateSpace::World);
		StartLocation.Z += FenceProperties.Height / 2;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AVerticalRailActor* SpawnedVerticalRailActor = GetWorld()->SpawnActor<AVerticalRailActor>(VerticalRailActorClass, StartLocation, StartRotation, SpawnParams);
		SpawnedVerticalRailActor->GenerateVerticalRailActor(FVector{ FenceProperties.Length, FenceProperties.Width, FenceProperties.Height });

		DistanceCovered += TotalSpacing;
	}
	GenerateProceduralHorizontalMesh();
}

void AFenceMeshActor::GenerateStaticHorizontalMesh() {
	int32 SplinePoints = SplineComponent->GetNumberOfSplinePoints();

	for (int32 i = 0; i < SplinePoints-1; ++i) {
		float DistanceBetweenPoints = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i + 1) - SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);

		// Upper Horizontal Beam
		UStaticMeshComponent* HorizontalStaticMeshComponentUp = NewObject<UStaticMeshComponent>(this);
		HorizontalStaticMeshComponentUp->RegisterComponent();
		HorizontalStaticMeshComponentUp->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

		HorizontalStaticMeshes.Add(HorizontalStaticMeshComponentUp);

		if (HorizontalStaticMesh) {
			HorizontalStaticMeshComponentUp->SetStaticMesh(HorizontalStaticMesh);
		}

		FVector StartLocation = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector EndLocation = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);

		FVector ForwardDirection = UKismetMathLibrary::GetDirectionUnitVector(StartLocation, EndLocation);
		FVector UpDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());
		FVector RightDirection = UKismetMathLibrary::RotateAngleAxis(ForwardDirection, 90, UpDirection);

		FRotator BeamRotation = UKismetMathLibrary::MakeRotationFromAxes(ForwardDirection, RightDirection, UpDirection);

		StartLocation += (ForwardDirection * (DistanceBetweenPoints / 2));
		StartLocation += (-RightDirection * ((FenceProperties.Width + 3) / 2));
		StartLocation += (UpDirection * (3 * FenceProperties.Height / 4));

		HorizontalStaticMeshComponentUp->SetWorldRotation(BeamRotation);
		HorizontalStaticMeshComponentUp->SetRelativeLocation(StartLocation);
		HorizontalStaticMeshComponentUp->SetWorldScale3D(FVector{ (DistanceBetweenPoints + 16) / 100, FenceProperties.Width / 10, FenceProperties.Height / 100 });

		// Lower Horizontal Beam
		UStaticMeshComponent* HorizontalStaticMeshComponentDown = NewObject<UStaticMeshComponent>(this);
		HorizontalStaticMeshComponentDown->RegisterComponent();
		HorizontalStaticMeshComponentDown->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

		HorizontalStaticMeshes.Add(HorizontalStaticMeshComponentDown);

		if (HorizontalStaticMesh) {
			HorizontalStaticMeshComponentDown->SetStaticMesh(HorizontalStaticMesh);
		}

		StartLocation -= (UpDirection * (3 * FenceProperties.Height / 4));
		StartLocation += (UpDirection * (FenceProperties.Height / 3));

		HorizontalStaticMeshComponentDown->SetWorldRotation(BeamRotation);
		HorizontalStaticMeshComponentDown->SetRelativeLocation(StartLocation);
		HorizontalStaticMeshComponentDown->SetWorldScale3D(FVector{ (DistanceBetweenPoints + 16) / 100, FenceProperties.Width / 10, FenceProperties.Height / 100 });
	}
}

void AFenceMeshActor::DestroyStaticHorizontalMesh() {
	for (int32 i = 0; i < HorizontalStaticMeshes.Num(); ++i) {
		if (HorizontalStaticMeshes[i]) {
			HorizontalStaticMeshes[i]->DestroyComponent();
			HorizontalStaticMeshes[i] = nullptr;
		}
	}

	HorizontalStaticMeshes.Empty();
}

void AFenceMeshActor::GenerateProceduralHorizontalMesh() {
	int32 SplinePoints = SplineComponent->GetNumberOfSplinePoints();

	for (int32 i = 0; i < SplinePoints - 1; ++i) {
		float Distance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i + 1) - SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);

		FVector StartLocation = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector EndLocation = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

		FVector ForwardDirection = UKismetMathLibrary::GetDirectionUnitVector(StartLocation, EndLocation);
		FVector UpDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());
		FVector RightDirection = UKismetMathLibrary::RotateAngleAxis(ForwardDirection, 90, UpDirection);

		FRotator BeamRotation = UKismetMathLibrary::MakeRotationFromAxes(ForwardDirection, RightDirection, UpDirection);

		// Upper Procedural Horizontal Beam
		StartLocation += (ForwardDirection * (Distance / 2));
		StartLocation += (-RightDirection * ((FenceProperties.Width + 3) / 2));
		StartLocation += (UpDirection * (3 * FenceProperties.Height / 4));

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AVerticalRailActor* HorizontalBeamActorUp = GetWorld()->SpawnActor<AVerticalRailActor>(StartLocation, BeamRotation, SpawnParams);
		HorizontalBeamActorUp->GenerateCube(0, FVector{ Distance + 16, (3 * FenceProperties.Width) / 10 , (10 * FenceProperties.Height) / 100 });

		// Lower Procedural Horizontal Beam
		StartLocation += (-UpDirection * (3 * FenceProperties.Height / 4));
		StartLocation += (UpDirection * (FenceProperties.Height / 3));

		AVerticalRailActor* HorizontalBeamActorDown = GetWorld()->SpawnActor<AVerticalRailActor>(StartLocation, BeamRotation, SpawnParams);
		HorizontalBeamActorDown->GenerateCube(0, FVector{ Distance + 16, (3 * FenceProperties.Width) / 10 , (10 * FenceProperties.Height) / 100 });
	}
}
