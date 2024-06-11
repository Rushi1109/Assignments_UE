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

void AMeshGenerator::FinishScatter() {
	GeneratedInstances = 0;

	if (AsyncScatterTask && !AsyncScatterTask->IsDone()) {
		AsyncScatterTask->EnsureCompletion();
	}

	delete AsyncScatterTask;
	AsyncScatterTask = nullptr;
}

void AMeshGenerator::ScatterMeshesInSelectedArea() {
	FinishScatter();

	AsyncScatterTask = new FAsyncTask<FAsyncScatterTask>(this);
	AsyncScatterTask->StartBackgroundTask();
}

void AMeshGenerator::AddMeshInstance(UStaticMesh* StaticMesh, const FTransform& Transform, UMaterialInstance* Material) {
	auto** HISMCPtr = HISMComponents.Find(StaticMesh);

	if (!this->IsValidLowLevel()) return;

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

	if (Material) {
		NewHISMC->SetMaterial(0, Material);
	}

	AsyncTask(ENamedThreads::GameThread, [NewHISMC, StaticMesh, Transform, this]() {
		NewHISMC->AddInstance(Transform, false);

		++GeneratedInstances;
		OnProgressed.ExecuteIfBound((float)GeneratedInstances / NumberOfInstances);
	});
}