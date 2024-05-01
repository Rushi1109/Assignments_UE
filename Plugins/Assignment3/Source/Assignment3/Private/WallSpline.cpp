// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSpline.h"

// Sets default values
AWallSpline::AWallSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(SceneComponent);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Actor Spline Component"));
	SplineComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWallSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallSpline::OnConstruction(const FTransform& Transform) {
	DestroySpline();

	GenerateSpline();
}

void AWallSpline::DestroySpline() {
	for (int i = 0; i < SplineComponentsArray.Num(); i++) {
		if (SplineComponentsArray[i]) {
			SplineComponentsArray[i]->DestroyComponent();
			SplineComponentsArray[i] = nullptr;
		}
	}

	SplineComponentsArray.Empty();
}

void AWallSpline::GenerateSpline() {
	int NumberOfSplinePoints = SplineComponent->GetNumberOfSplinePoints();
	for (int i = 0; i < NumberOfSplinePoints - 1; i++) {
		SplineComponent->SetSplinePointType(i, ESplinePointType::Linear);

		FVector StartPosition, StartTangent;
		SplineComponent->GetLocationAndTangentAtSplinePoint(i, StartPosition, StartTangent, ESplineCoordinateSpace::World);

		FVector EndPosition, EndTangent;
		SplineComponent->GetLocationAndTangentAtSplinePoint(i + 1, EndPosition, EndTangent, ESplineCoordinateSpace::World);

		USplineMeshComponent* MeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		MeshComponent->RegisterComponent();
		if (SourceMesh) {
			MeshComponent->SetStaticMesh(SourceMesh);
		}
		MeshComponent->SetStartAndEnd(StartPosition, StartTangent, EndPosition, EndTangent, true);
		MeshComponent->SetupAttachment(SplineComponent);

		SplineComponentsArray.Add(MeshComponent);
	}
}
