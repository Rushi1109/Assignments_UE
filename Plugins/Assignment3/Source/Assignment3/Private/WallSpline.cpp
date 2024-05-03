// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSpline.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWallSpline::AWallSpline() : SourceMesh{ nullptr }, SourceMeshMaterial{ nullptr } {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(SceneComponent);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Actor Spline Component"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->ClearSplinePoints();
	//SplineComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//SplineComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	SourceMesh = LoadObject<UStaticMesh>(this, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Architecture/Wall_400x200.Wall_400x200'"));
	SourceMeshMaterial = LoadObject<UMaterial>(this, TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Concrete_Poured.M_Concrete_Poured'"));
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
	int32 NumberOfSplinePoints = SplineComponent->GetNumberOfSplinePoints();

	FVector ZeroVector{};
	SplineComponent->SetTangentsAtSplinePoint(NumberOfSplinePoints - 1, ZeroVector, ZeroVector, ESplineCoordinateSpace::Local);

	FVector StartPosition{}, StartTangent{};
	SplineComponent->GetLocationAndTangentAtSplinePoint(NumberOfSplinePoints - 2, StartPosition, StartTangent, ESplineCoordinateSpace::World);

	FVector EndPosition{}, EndTangent{};
	SplineComponent->GetLocationAndTangentAtSplinePoint(NumberOfSplinePoints - 1, EndPosition, EndTangent, ESplineCoordinateSpace::World);

	USplineMeshComponent* MeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
	MeshComponent->RegisterComponent();
	if (SourceMesh) {
		MeshComponent->SetMobility(EComponentMobility::Movable);
		MeshComponent->SetStaticMesh(SourceMesh);
		if (SourceMeshMaterial) {
			SourceMesh->SetMaterial(0, SourceMeshMaterial);
		}
	}
	FVector Tangent = UKismetMathLibrary::GetDirectionUnitVector(StartPosition, EndPosition);

	StartPosition -= Tangent*10;
	EndPosition += Tangent*10;

	MeshComponent->SetStartAndEnd(StartPosition, Tangent, EndPosition, Tangent, true);
	MeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SplineComponentsArray.Add(MeshComponent);
}

void AWallSpline::CreateWall(FVector& Location) {
	SplineComponent->AddSplinePoint(Location, ESplineCoordinateSpace::World, true);

	GenerateSpline();
}

void AWallSpline::RemoveLastSplinePoint() {
	int32 NumberOfSplinePoints = SplineComponent->GetNumberOfSplinePoints();

	if (!SplineComponentsArray.IsEmpty()) {
		USplineMeshComponent* SplineMeshComponent = SplineComponentsArray.Pop(true);
		SplineMeshComponent->DestroyComponent();
	}
	
	if (NumberOfSplinePoints - 1) {
		SplineComponent->RemoveSplinePoint(NumberOfSplinePoints - 1);
	}
}
