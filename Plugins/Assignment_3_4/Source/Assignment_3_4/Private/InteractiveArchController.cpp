// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveArchController.h"
#include "OrthographicPawn.h"
#include "IsometricPawn.h"
#include "PerspectivePawn.h"

AInteractiveArchController::AInteractiveArchController() : Widget{ nullptr }, LastHitLocation{0, 0, 200}, CurrentHitActor{ nullptr }, bIsArchMeshActor{ false }, LeftClickAction{ nullptr }, ToggleVisibilityAction{ nullptr }, TogglePawnAction{ nullptr },  MeshGeneratorMappingContext{ nullptr }, PawnIndex{ -1 } {
	PawnReferences.Add(APerspectivePawn::StaticClass());
	PawnReferences.Add(AOrthographicPawn::StaticClass());
	PawnReferences.Add(AIsometricPawn::StaticClass());
}

void AInteractiveArchController::BeginPlay() {
	Super::BeginPlay();

	SetShowMouseCursor(true);

	Widget = CreateWidget<USelectionWidget>(this, SelectionWidget, TEXT("Selection Widget"));
	
	Widget->ScrollBox1->OnMeshAssetReceived.BindUFunction(this, "HandleMeshSelection");
	Widget->ScrollBox1->OnMaterialAssetReceived.BindUFunction(this, "HandleMaterialSelection");
	Widget->ScrollBox1->OnTextureAssetReceived.BindUFunction(this, "HandleTextureSelection");

	Widget->ScrollBox2->OnMeshAssetReceived.BindUFunction(this, "HandleMeshSelection");
	Widget->ScrollBox2->OnMaterialAssetReceived.BindUFunction(this, "HandleMaterialSelection");
	Widget->ScrollBox2->OnTextureAssetReceived.BindUFunction(this, "HandleTextureSelection");

	Widget->ScrollBox3->OnMeshAssetReceived.BindUFunction(this, "HandleMeshSelection");
	Widget->ScrollBox3->OnMaterialAssetReceived.BindUFunction(this, "HandleMaterialSelection");
	Widget->ScrollBox3->OnTextureAssetReceived.BindUFunction(this, "HandleTextureSelection");

	SetInputMode(InputMode);

	HandleTogglePawn();
}

void AInteractiveArchController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	LeftClickAction = NewObject<UInputAction>(this);
	LeftClickAction->ValueType = EInputActionValueType::Boolean;
	ToggleVisibilityAction = NewObject<UInputAction>(this);
	ToggleVisibilityAction->ValueType = EInputActionValueType::Boolean;

	MeshGeneratorMappingContext = NewObject<UInputMappingContext>(this);
	MeshGeneratorMappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);
	MeshGeneratorMappingContext->MapKey(ToggleVisibilityAction, EKeys::Tab);

	// Context for TogglePawn
	TogglePawnAction = NewObject<UInputAction>(this);
	TogglePawnAction->ValueType = EInputActionValueType::Boolean;

	SwitchMappingContext = NewObject<UInputMappingContext>(this);
	SwitchMappingContext->MapKey(TogglePawnAction, EKeys::P);

	EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleLeftClick);
	EnhancedInputComponent->BindAction(ToggleVisibilityAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleTabKey);
	EnhancedInputComponent->BindAction(TogglePawnAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleTogglePawn);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) {
		Subsystem->AddMappingContext(MeshGeneratorMappingContext, 0);
		Subsystem->AddMappingContext(SwitchMappingContext, 0);
	}
}

void AInteractiveArchController::HandleLeftClick() {
	if (!Widget->IsInViewport()) {
		Widget->AddToViewport();
	}

	if (Widget->ScrollBox1->ScrollBoxAssetType == EAssetType::MeshData) {
		Widget->ScrollBox1->SetVisibility(ESlateVisibility::Visible);
		Widget->ScrollBox2->SetVisibility(ESlateVisibility::Hidden);
		Widget->ScrollBox3->SetVisibility(ESlateVisibility::Hidden);
	} 
	else if (Widget->ScrollBox2->ScrollBoxAssetType == EAssetType::MeshData) {
		Widget->ScrollBox2->SetVisibility(ESlateVisibility::Visible);
		Widget->ScrollBox1->SetVisibility(ESlateVisibility::Hidden);
		Widget->ScrollBox3->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Widget->ScrollBox3->ScrollBoxAssetType == EAssetType::MeshData) {
		Widget->ScrollBox3->SetVisibility(ESlateVisibility::Visible);
		Widget->ScrollBox1->SetVisibility(ESlateVisibility::Hidden);
		Widget->ScrollBox2->SetVisibility(ESlateVisibility::Hidden);
	}

	FVector WorldLocation{}, WorldDirection{};

	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = WorldLocation + (WorldDirection * 10000.0);

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.bTraceComplex = true;

		FHitResult HitResult;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams)) {
			if (CurrentHitActor = HitResult.GetActor(), CurrentHitActor) {
				LastHitLocation = HitResult.Location;
				if (CurrentHitActor->IsA(AArchMeshActor::StaticClass())) {
					bIsArchMeshActor = true;
					GetPawn()->SetActorLocation(LastHitLocation + FVector{ 0, 0, 100 });

					Widget->SetVisibility(ESlateVisibility::Visible);
					Widget->ScrollBox1->SetVisibility(ESlateVisibility::Visible);
					Widget->ScrollBox2->SetVisibility(ESlateVisibility::Visible);
					Widget->ScrollBox3->SetVisibility(ESlateVisibility::Visible);

					auto BoundingBox = Cast<AArchMeshActor>(CurrentHitActor)->GetStaticMeshComponent()->GetStaticMesh()->GetBoundingBox();
					auto Offset = BoundingBox.Max.Z;
					LastHitLocation = CurrentHitActor->GetActorLocation() - FVector(0, 0, Offset);
				}
				else {
					bIsArchMeshActor = false;

					Widget->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}
}

void AInteractiveArchController::HandleTabKey() {	
	if (Widget->IsInViewport()) {
		ESlateVisibility SlateVisibility = Widget->GetVisibility();

		switch (SlateVisibility) {
		case ESlateVisibility::Visible:
			SlateVisibility = ESlateVisibility::Hidden;
			break;
		case ESlateVisibility::Hidden:
			SlateVisibility = ESlateVisibility::Visible;
			break;
		default:
			SlateVisibility = ESlateVisibility::Hidden;
			break;
		}

		Widget->SetVisibility(SlateVisibility);
	}
}

void AInteractiveArchController::HandleTogglePawn() {
	PawnIndex = (PawnIndex + 1) % PawnReferences.Num();

	if (GetPawn()) {
		GetPawn()->Destroy();
	}

	UEnhancedInputLocalPlayerSubsystem* SubSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (SubSystem) {
		SubSystem->ClearAllMappings();
	}

	FActorSpawnParameters SpawnActorParams;
	SpawnActorParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FRotator Rotator = FRotator::ZeroRotator;

	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnReferences[PawnIndex], LastHitLocation + FVector{0,0, 50}, Rotator, SpawnActorParams);

	if (SpawnedPawn) {
		Possess(SpawnedPawn);
	}

	SubSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (SubSystem) {
		SubSystem->AddMappingContext(SwitchMappingContext, 0);
		SubSystem->AddMappingContext(MeshGeneratorMappingContext, 0);
	}
}

AArchMeshActor* AInteractiveArchController::SpawnMeshFromMeshData() {
	if (this->MeshData.MeshAsset) {
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		auto BoundingBox = this->MeshData.MeshAsset->GetBoundingBox();
		auto Offset = BoundingBox.Max.Z;

		auto ArchMeshActor = GetWorld()->SpawnActor<AArchMeshActor>(LastHitLocation + FVector(0, 0, Offset), FRotator::ZeroRotator, SpawnParameters);

		ArchMeshActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
		ArchMeshActor->GetStaticMeshComponent()->SetStaticMesh(this->MeshData.MeshAsset);
		bIsArchMeshActor = true;

		CurrentHitActor = ArchMeshActor;

		Widget->ScrollBox1->SetVisibility(ESlateVisibility::Visible);
		Widget->ScrollBox2->SetVisibility(ESlateVisibility::Visible);
		Widget->ScrollBox3->SetVisibility(ESlateVisibility::Visible);

		return ArchMeshActor;
	}

	return nullptr;
}

void AInteractiveArchController::HandleMeshSelection(const FMeshData& Mesh) {
	this->MeshData = Mesh;

	if (bIsArchMeshActor) {
		CurrentHitActor->Destroy();

		SpawnMeshFromMeshData();
	}
	else{
		SpawnMeshFromMeshData();
	}
	
	if (GetPawn()->IsA(APerspectivePawn::StaticClass())) {
		APerspectivePawn* PerspectivePawn = Cast<APerspectivePawn>(GetPawn());
		PerspectivePawn->SetActorLocation(LastHitLocation + FVector{ 0, 0, 100 });
	}
	else {
		GetPawn()->SetActorLocation(LastHitLocation + FVector{ 0, 0, 100 });
	}
}

void AInteractiveArchController::HandleMaterialSelection(const FMaterialData& Material) {
	Cast<AArchMeshActor>(CurrentHitActor)->GetStaticMeshComponent()->SetMaterial(0, Material.MaterialAsset);
}

void AInteractiveArchController::HandleTextureSelection(const FTextureData& Texture) {
	UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Cast<AArchMeshActor>(CurrentHitActor)->GetStaticMeshComponent()->GetMaterial(0));

	if (!DynamicMaterial) {
		MaterialInstance = UMaterialInstanceDynamic::Create(Cast<AArchMeshActor>(CurrentHitActor)->GetStaticMeshComponent()->GetMaterial(0), this);
	}

	MaterialInstance->SetTextureParameterValue(TEXT("Texture"), Texture.TextureAsset);
	Cast<AArchMeshActor>(CurrentHitActor)->GetStaticMeshComponent()->SetMaterial(0, MaterialInstance);
}