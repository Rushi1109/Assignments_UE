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
		if (StaticMeshComponents[i].HandrailLeftComponent) {
			StaticMeshComponents[i].HandrailLeftComponent->DestroyComponent();
			StaticMeshComponents[i].HandrailLeftComponent = nullptr;
		}
		if (StaticMeshComponents[i].HandrailRightComponent) {
			StaticMeshComponents[i].HandrailRightComponent->DestroyComponent();
			StaticMeshComponents[i].HandrailRightComponent = nullptr;
		}
		if (StaticMeshComponents[i].RailingLeftComponent) {
			StaticMeshComponents[i].RailingLeftComponent->DestroyComponent();
			StaticMeshComponents[i].RailingLeftComponent = nullptr;
		}
		if (StaticMeshComponents[i].RailingRightComponent) {
			StaticMeshComponents[i].RailingRightComponent->DestroyComponent();
			StaticMeshComponents[i].RailingRightComponent = nullptr;
		}
		if (StaticMeshComponents[i].FloorComponent) {
			StaticMeshComponents[i].FloorComponent->DestroyComponent();
			StaticMeshComponents[i].FloorComponent = nullptr;
		}
	}

	StaticMeshComponents.Empty();

	for (int i = 0; i < NumberOfSteps; i++) {
		FString StairName = "Stair" + FString::FromInt(i);
		UStaticMeshComponent* StepComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *StairName);
		//StaticMeshComponents.Add(StepComponent);

		StepComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		StepComponent->RegisterComponentWithWorld(GetWorld());

		FStaircaseStruct Staircase;
		Staircase.FloorComponent = StepComponent;

		if (SourceMesh) {
			StepComponent->SetStaticMesh(SourceMesh);

			FVector SourceMeshSize = SourceMesh->GetBounds().GetBox().GetSize();
			
			switch (StairType)
			{
			case EStaircaseType::ClosedStairs:
				StepComponent->SetRelativeScale3D(Dimensions);
				StepComponent->SetRelativeLocation(FVector(i * Dimensions.X * SourceMeshSize.X, 0, i * Dimensions.Z * SourceMeshSize.Z));
				break;
			case EStaircaseType::OpenStairs:
				StepComponent->SetRelativeScale3D(Dimensions);
				StepComponent->SetRelativeLocation(FVector(i * Dimensions.X * SourceMeshSize.X * (TranslationOffset.X / 100), 0, i * Dimensions.Z * SourceMeshSize.Z * (TranslationOffset.Z / 100)));
				break;
			case EStaircaseType::BoxStairs:
				StepComponent->SetRelativeScale3D(FVector(Dimensions.X, Dimensions.Y, Dimensions.Z * (i+1)));
				StepComponent->SetRelativeLocation(FVector(i * Dimensions.X * SourceMeshSize.X, 0, i * Dimensions.Z * SourceMeshSize.Z / 2));
				break;
			default:
				break;
			}

			if (EnableRailing) {
				FString RailingLeftName = StairName + " Left Railing";
				UStaticMeshComponent* RailingLeftMeshComponent = NewObject<UStaticMeshComponent>(StepComponent, UStaticMeshComponent::StaticClass(), *RailingLeftName);

				FString RailingRightName = StairName + " Right Railing";
				UStaticMeshComponent* RailingRightMeshComponent = NewObject<UStaticMeshComponent>(StepComponent, UStaticMeshComponent::StaticClass(), *RailingRightName);

				FString HandrailLeftName = StairName + " Left Handrail";
				UStaticMeshComponent* HandrailLeftMeshComponent = NewObject<UStaticMeshComponent>(StepComponent, UStaticMeshComponent::StaticClass(), *HandrailLeftName);

				FString HandrailRightName = StairName + " Right Handrail";
				UStaticMeshComponent* HandrailRightMeshComponent = NewObject<UStaticMeshComponent>(StepComponent, UStaticMeshComponent::StaticClass(), *HandrailRightName);

				RailingLeftMeshComponent->AttachToComponent(StepComponent, FAttachmentTransformRules::KeepRelativeTransform);
				RailingLeftMeshComponent->RegisterComponentWithWorld(GetWorld());

				RailingRightMeshComponent->AttachToComponent(StepComponent, FAttachmentTransformRules::KeepRelativeTransform);
				RailingRightMeshComponent->RegisterComponentWithWorld(GetWorld());

				HandrailLeftMeshComponent->AttachToComponent(StepComponent, FAttachmentTransformRules::KeepRelativeTransform);
				HandrailLeftMeshComponent->RegisterComponentWithWorld(GetWorld());

				HandrailRightMeshComponent->AttachToComponent(StepComponent, FAttachmentTransformRules::KeepRelativeTransform);
				HandrailRightMeshComponent->RegisterComponentWithWorld(GetWorld());

				Staircase.RailingLeftComponent = RailingLeftMeshComponent;
				Staircase.RailingRightComponent = RailingRightMeshComponent;
				Staircase.HandrailLeftComponent = HandrailLeftMeshComponent;
				Staircase.HandrailRightComponent = HandrailRightMeshComponent;

				if (RailingMesh) {
					RailingLeftMeshComponent->SetStaticMesh(RailingMesh);
					RailingRightMeshComponent->SetStaticMesh(RailingMesh);

					HandrailLeftMeshComponent->SetStaticMesh(RailingMesh);
					HandrailRightMeshComponent->SetStaticMesh(RailingMesh);

					FVector RailingMeshSize = RailingMesh->GetBounds().GetBox().GetSize();

					if (StairType == EStaircaseType::BoxStairs) {
						double RailingTotalSize = 3 * 100;
						double StepTotalSize = SourceMeshSize.Z * Dimensions.Z * (i + 1);

						RailingLeftMeshComponent->SetWorldScale3D(FVector(0.25 * 100 / RailingMeshSize.X, 0.025 * 100 / RailingMeshSize.Y, 3 * 100 / RailingMeshSize.Z));
						RailingRightMeshComponent->SetWorldScale3D(FVector(0.25 * 100 / RailingMeshSize.X, 0.025 * 100 / RailingMeshSize.Y, 3 * 100 / RailingMeshSize.Z));

						RailingLeftMeshComponent->SetRelativeLocation(FVector(0, -45, 50 + ((RailingTotalSize / (2 * StepTotalSize)) * 100)));
						RailingRightMeshComponent->SetRelativeLocation(FVector(0, 45, 50 + ((RailingTotalSize / (2 * StepTotalSize)) * 100)));
					}
					else if (StairType == EStaircaseType::ClosedStairs){
						double RailingTotalSize = 100 * 5 * Dimensions.Z;
						double StepTotalSize = SourceMeshSize.Z * Dimensions.Z;

						RailingLeftMeshComponent->SetRelativeScale3D(FVector(0.25 * 100 / RailingMeshSize.X, 0.025 * 100 / RailingMeshSize.Y, 5 * 100 / RailingMeshSize.Z));
						RailingRightMeshComponent->SetRelativeScale3D(FVector(0.25 * 100 / RailingMeshSize.X, 0.025 * 100 / RailingMeshSize.Y, 5 * 100 / RailingMeshSize.Z));

						RailingLeftMeshComponent->SetRelativeLocation(FVector(0, -45, (((RailingTotalSize - StepTotalSize) / (2 * StepTotalSize)) + 1) * 100));
						RailingRightMeshComponent->SetRelativeLocation(FVector(0, 45, (((RailingTotalSize - StepTotalSize) / (2 * StepTotalSize)) + 1) * 100));
					}
					else {
						double RailingTotalSize = 100 * 5 * Dimensions.Z;
						double StepTotalSize = SourceMeshSize.Z * Dimensions.Z;

						RailingLeftMeshComponent->SetRelativeScale3D(FVector(0.25 * 100 / RailingMeshSize.X, 0.025 * 100 / RailingMeshSize.Y, 5 * 100 / RailingMeshSize.Z));
						RailingRightMeshComponent->SetRelativeScale3D(FVector(0.25 * 100 / RailingMeshSize.X, 0.025 * 100 / RailingMeshSize.Y, 5 * 100 / RailingMeshSize.Z));

						RailingLeftMeshComponent->SetRelativeLocation(FVector(0, -45, (((RailingTotalSize - StepTotalSize) / (2 * StepTotalSize)) + 1) * 100));
						RailingRightMeshComponent->SetRelativeLocation(FVector(0, 45, (((RailingTotalSize - StepTotalSize) / (2 * StepTotalSize)) + 1) * 100));
					}
				}
			}
		}

		StaticMeshComponents.Add(Staircase);


		

		
		
		//UE_LOG(LogTemp, Warning, TEXT("Left Railing offset: %s"), *(StepComponent->GetRelativeLocation().ToCompactString()));
		//
		
		//UE_LOG(LogTemp, Warning, TEXT("Right Railing offset: %s"), *(StepComponent->GetRelativeLocation().ToCompactString()));
	}
}

FStaircaseStruct::FStaircaseStruct() : FloorComponent{ nullptr }, RailingLeftComponent{ nullptr }, RailingRightComponent{ nullptr }, HandrailLeftComponent{ nullptr }, HandrailRightComponent{ nullptr } {}
