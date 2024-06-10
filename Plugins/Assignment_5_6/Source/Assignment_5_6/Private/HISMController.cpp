// Fill out your copyright notice in the Description page of Project Settings.


#include "HISMController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AHISMController::AHISMController() : bIsAreaSelected{ false }, SelectionAreaShape{ nullptr }, WorldLocation{ 0.0, 0.0, 0.0 }, WorldDirection{ 0.0, 0.0, 0.0 } {
	
}

void AHISMController::BeginPlay() {
	Super::BeginPlay();
	
	SetShowMouseCursor(true);
	SetInputMode(InputMode);

	if (MeshGeneratorUIClass) {
		MeshGeneratorUI = CreateWidget<UMeshGeneratorUI>(this, MeshGeneratorUIClass);
		MeshGeneratorUI->HideBoxFields();
		MeshGeneratorUI->AddToViewport(1);

		MeshGeneratorUI->ComboBox->OnSelectionChanged.AddDynamic(this, &AHISMController::HandleShapeSelectionChange);
		MeshGeneratorUI->SphericalRadius->OnValueChanged.AddDynamic(this, &AHISMController::GenerateNewSphere);
		MeshGeneratorUI->CubeDimensionX->OnValueChanged.AddDynamic(this, &AHISMController::GenerateNewBox);
		MeshGeneratorUI->CubeDimensionY->OnValueChanged.AddDynamic(this, &AHISMController::GenerateNewBox);
		MeshGeneratorUI->CubeDimensionZ->OnValueChanged.AddDynamic(this, &AHISMController::GenerateNewBox);
		MeshGeneratorUI->GenerateMeshButton->OnClicked.AddDynamic(this, &AHISMController::ScatterMeshes);
	}

	if (SelectionAreaClass) {
		SelectionAreaShape = GetWorld()->SpawnActor<ASelectionArea>(SelectionAreaClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	if (SelectionAreaShape && MeshGeneratorClass) {
		MeshGenerator = NewObject<AMeshGenerator>(this, MeshGeneratorClass);

		MeshGenerator->OnProgressed.BindUObject(this, &AHISMController::UpdateProgressBar);
	}
}

void AHISMController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bIsAreaSelected) {
		if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
			FVector TraceStart = WorldLocation;
			FVector TraceEnd = WorldLocation + (WorldDirection * 10000.0);

			FCollisionQueryParams CollisionQueryParams;
			CollisionQueryParams.bTraceComplex = true;
			CollisionQueryParams.AddIgnoredActor(SelectionAreaShape);

			FHitResult HitResult;

			if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams)) {
				if (HitResult.bBlockingHit) {
					HitResult.Location.Z = 0.0;
					SelectionAreaShape->SetActorLocation(HitResult.Location);
				}
			}
		}
	}
}

void AHISMController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	LeftClickAction = NewObject<UInputAction>(this);
	LeftClickAction->ValueType = EInputActionValueType::Boolean;

	MeshGeneratorMappingContext = NewObject<UInputMappingContext>(this);
	MeshGeneratorMappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);

	EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AHISMController::HandleLeftClick);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) {
		Subsystem->AddMappingContext(MeshGeneratorMappingContext, 0);
	}
}

void AHISMController::HandleLeftClick() {
	bIsAreaSelected = !bIsAreaSelected;
}

void AHISMController::HandleShapeSelectionChange(FString SelectedItem, ESelectInfo::Type SelectionType) {
	if (SelectedItem == "Spherical" && MeshGeneratorUI && SelectionAreaShape) {
		SelectionAreaShape->ShapeType = EShapeType::Spherical;
		MeshGeneratorUI->HideBoxFields();

		float Radius = MeshGeneratorUI->CubeDimensionZ->GetValue();
		GenerateNewSphere(Radius);
	}
	else if (SelectedItem == "Box" && MeshGeneratorUI && SelectionAreaShape) {
		SelectionAreaShape->ShapeType = EShapeType::Box;
		MeshGeneratorUI->HideSphereFields();

		GenerateNewBox(float{0.0});
	}
}


void AHISMController::GenerateNewSphere(float InValue) {
	InValue = MeshGeneratorUI->SphericalRadius->GetValue();
	if (SelectionAreaShape) {
		SelectionAreaShape->GenerateSphere(0, InValue, 30, 50, InValue);
	}
}

void AHISMController::GenerateNewBox(float InValue) {
	if (SelectionAreaShape) {
		float DimensionX = MeshGeneratorUI->CubeDimensionX->GetValue();
		float DimensionY = MeshGeneratorUI->CubeDimensionY->GetValue();
		float DimensionZ = MeshGeneratorUI->CubeDimensionZ->GetValue();

		SelectionAreaShape->GenerateBox(0, DimensionX, DimensionY, DimensionZ, (float)DimensionZ / 2);
	}
}

void AHISMController::ScatterMeshes() {
	if (MeshGenerator) {
		if (SelectionAreaShape->ShapeType == EShapeType::Spherical) {
			MeshGenerator->AreaParams(SelectionAreaShape, FVector{ MeshGeneratorUI->SphericalRadius->GetValue() }, MeshGeneratorUI->InstanceCount->GetValue());
		}
		else {
			MeshGenerator->AreaParams(SelectionAreaShape, FVector{ MeshGeneratorUI->CubeDimensionX->GetValue(), MeshGeneratorUI->CubeDimensionY->GetValue(), MeshGeneratorUI->CubeDimensionZ->GetValue() }, MeshGeneratorUI->InstanceCount->GetValue());
		}

		MeshGeneratorUI->ShowProgressBar();
		MeshGenerator->ScatterMeshesInSelectedArea();
	}
}

void AHISMController::UpdateProgressBar(float InPercent) {
	if (MeshGenerator && MeshGeneratorUI) {
		MeshGeneratorUI->UpdateProgressBar(InPercent);
	}
}