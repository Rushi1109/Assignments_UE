// Fill out your copyright notice in the Description page of Project Settings.


#include "StaircaseActor.h"

// Sets default values
AStaircaseActor::AStaircaseActor() : NumberOfSteps{1}, Dimensions{1.0, 1.0, 1.0}, TranslationOffset{100.0, 0.0, 100.0}, EnableRailing{false}
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* defaultSceneRoot{ CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")) };
	SetRootComponent(defaultSceneRoot);
}

// Called when the game starts or when spawned
void AStaircaseActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStaircaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStaircaseActor::OnConstruction(const FTransform& Transform) {
	UE_LOG(LogTemp, Warning, TEXT("Inside OnConstruction"));

	for (int i = 0; i < StaticMeshComponents.Num(); i++) {
		if (StaticMeshComponents[i]) {
			StaticMeshComponents[i]->DestroyComponent();
		}
		StaticMeshComponents[i] = nullptr;
	}

	StaticMeshComponents.Empty();

	for (int i = 0; i < NumberOfSteps; i++) {
		FString StairName = "Stair" + FString::FromInt(i);
		UStaticMeshComponent* StepComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *StairName);
		StaticMeshComponents.Add(StepComponent);

		StepComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		StepComponent->RegisterComponentWithWorld(GetWorld());

		if (SourceMesh) {
			StepComponent->SetStaticMesh(SourceMesh);

			FVector MeshSize = SourceMesh->GetBounds().GetBox().GetSize();
			
			switch (StairType)
			{
			case EStaircaseEnum::ClosedStairs:
				StepComponent->SetRelativeScale3D(Dimensions);
				StepComponent->SetRelativeLocation(FVector(i * Dimensions.X * MeshSize.X, 0, i * Dimensions.Z * MeshSize.Z));
				break;
			case EStaircaseEnum::OpenStairs:
				StepComponent->SetRelativeScale3D(Dimensions);
				StepComponent->SetRelativeLocation(FVector(i * Dimensions.X * MeshSize.X * (TranslationOffset.X / 100), 0, i * Dimensions.Z * MeshSize.Z * (TranslationOffset.Z / 100)));
				break;
			case EStaircaseEnum::BoxStairs:
				StepComponent->SetRelativeScale3D(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z * (i+1)));
				StepComponent->SetRelativeLocation(FVector(i * Dimensions.X * MeshSize.X, 0, i * Dimensions.Z * MeshSize.Z / 2));
				break;
			default:
				break;
			}

			if (EnableRailing) {
				FString RailingLeftName = StairName + " Left Railing";
				UStaticMeshComponent* RailingLeftMesh = NewObject<UStaticMeshComponent>(StepComponent, UStaticMeshComponent::StaticClass(), *RailingLeftName);

				FString RailingRightName = StairName + " Right Railing";
				UStaticMeshComponent* RailingRightMesh = NewObject<UStaticMeshComponent>(StepComponent, UStaticMeshComponent::StaticClass(), *RailingRightName);

				RailingLeftMesh->AttachToComponent(StepComponent, FAttachmentTransformRules::KeepRelativeTransform);
				RailingLeftMesh->RegisterComponentWithWorld(GetWorld());

				RailingRightMesh->AttachToComponent(StepComponent, FAttachmentTransformRules::KeepRelativeTransform);
				RailingRightMesh->RegisterComponentWithWorld(GetWorld());

				if (RailingMesh) {
					RailingLeftMesh->SetStaticMesh(RailingMesh);
					RailingRightMesh->SetStaticMesh(RailingMesh);

					FVector RailingMeshSize = RailingMesh->GetBounds().GetBox().GetSize();

					RailingLeftMesh->SetRelativeScale3D(FVector(Dimensions.X, 0.02, Dimensions.Z));
					RailingRightMesh->SetRelativeScale3D(FVector(Dimensions.X, 0.02, Dimensions.Z));
					RailingLeftMesh->SetRelativeLocation(FVector(0, -45, (Dimensions.Z * RailingMeshSize.Z / 2) + (Dimensions.Z * MeshSize.Z / 2)));
					RailingRightMesh->SetRelativeLocation(FVector(0, 45, (Dimensions.Z * RailingMeshSize.Z / 2) + (Dimensions.Z * MeshSize.Z / 2)));
				}
			}
		}
		

		
		
		//UE_LOG(LogTemp, Warning, TEXT("Left Railing offset: %s"), *(StepComponent->GetRelativeLocation().ToCompactString()));
		//
		
		//UE_LOG(LogTemp, Warning, TEXT("Right Railing offset: %s"), *(StepComponent->GetRelativeLocation().ToCompactString()));
	}
}
