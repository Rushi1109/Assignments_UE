// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveArchController.h"

AInteractiveArchController::AInteractiveArchController() : Widget{ nullptr }, CurrentHitActor{ nullptr }, bIsArchMeshActor{false}, LeftClickAction{nullptr}, ToggleVisibilityAction{nullptr}, InputMappingContext{nullptr} {}

void AInteractiveArchController::BeginPlay() {
	Super::BeginPlay();

	SetShowMouseCursor(true);

	Widget = CreateWidget<USelectionWidget>(this, SelectionWidget, TEXT("Selection Widget"));
	
	Widget->ScrollBox1->OnMeshAssetReceived.BindUFunction(this, "PopulateMeshData");
	Widget->ScrollBox1->OnMaterialAssetReceived.BindUFunction(this, "PopulateMaterialData");
	Widget->ScrollBox1->OnTextureAssetReceived.BindUFunction(this, "PopulateTextureData");

	Widget->ScrollBox2->OnMeshAssetReceived.BindUFunction(this, "PopulateMeshData");
	Widget->ScrollBox2->OnMaterialAssetReceived.BindUFunction(this, "PopulateMaterialData");
	Widget->ScrollBox2->OnTextureAssetReceived.BindUFunction(this, "PopulateTextureData");

	Widget->ScrollBox3->OnMeshAssetReceived.BindUFunction(this, "PopulateMeshData");
	Widget->ScrollBox3->OnMaterialAssetReceived.BindUFunction(this, "PopulateMaterialData");
	Widget->ScrollBox3->OnTextureAssetReceived.BindUFunction(this, "PopulateTextureData");

	SetInputMode(InputMode);
}

void AInteractiveArchController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	LeftClickAction = NewObject<UInputAction>(this, TEXT("LeftClickAction"));
	LeftClickAction->ValueType = EInputActionValueType::Boolean;
	ToggleVisibilityAction = NewObject<UInputAction>(this, TEXT("ToggleVisibilityAction"));
	ToggleVisibilityAction->ValueType = EInputActionValueType::Boolean;

	InputMappingContext = NewObject<UInputMappingContext>(this, TEXT("InputMappingContext"));
	InputMappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);
	InputMappingContext->MapKey(ToggleVisibilityAction, EKeys::Tab);

	EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleLeftClick);
	EnhancedInputComponent->BindAction(ToggleVisibilityAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleTabKey);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(InputMappingContext, 0);
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

void AInteractiveArchController::PopulateMeshData(const FMeshData& Mesh) {
	this->MeshData = Mesh;

	if (bIsArchMeshActor) {
		CurrentHitActor->Destroy();

		SpawnMeshFromMeshData();
	}
	else{
		SpawnMeshFromMeshData();
	}
}

void AInteractiveArchController::PopulateMaterialData(const FMaterialData& Material) {
	this->MaterialData = Material;

	Cast<AArchMeshActor>(CurrentHitActor)->GetStaticMeshComponent()->SetMaterial(0, Material.MaterialAsset);
}

void AInteractiveArchController::PopulateTextureData(const FTextureData& Texture) {
	this->TextureData = Texture;
}