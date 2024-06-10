// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshGenerator.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Sets default values
AMeshGenerator::AMeshGenerator() : DataAsset{ nullptr }, SelecetionArea{ nullptr }, NumberOfInstances{ 50 }, AsyncScatterTask{ nullptr } {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
}

void AMeshGenerator::AreaParams(ASelectionArea* InSelectionArea, const FVector& InAreaDimensions, int32 InInstanceCount) {
	SelecetionArea = InSelectionArea;
	SetDimensions(InAreaDimensions);
	SetNumberOfInstances(InInstanceCount);
}

// Called when the game starts or when spawned
void AMeshGenerator::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AMeshGenerator::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AMeshGenerator::ScatterMeshesInSelectedArea() {
	AsyncScatterTask = new FAsyncTask<FAsyncScatterTask>(this);
	AsyncScatterTask->StartBackgroundTask();
}

void AMeshGenerator::AddMeshInstance(UStaticMesh* StaticMesh, const FTransform& Transform) {
	auto** HISMCPtr = HISMComponents.Find(StaticMesh);

	UHierarchicalInstancedStaticMeshComponent* NewHISMC;
	if (HISMCPtr && *HISMCPtr && (*HISMCPtr)->IsValidLowLevel()) {
		NewHISMC = *HISMCPtr;
	}
	else {
		NewHISMC = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
		NewHISMC->RegisterComponentWithWorld(GetWorld());
		NewHISMC->SetStaticMesh(StaticMesh);

		HISMComponents.Add(StaticMesh, NewHISMC);
	}
	AsyncTask(ENamedThreads::GameThread, [NewHISMC, StaticMesh, Transform]() {
		NewHISMC->AddInstance(Transform, false);

		});
}

