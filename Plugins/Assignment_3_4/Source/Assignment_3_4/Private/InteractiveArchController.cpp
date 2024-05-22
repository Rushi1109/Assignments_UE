// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveArchController.h"
#include "OrthographicPawn.h"
#include "IsometricPawn.h"
#include "PerspectivePawn.h"
#include "Widgets/SelectionWidget.h"

AInteractiveArchController::AInteractiveArchController() : MeshGeneratorSelectionWidget{ nullptr }, LastHitLocation{ 0, 0, 200 }, CurrentHitActor{ nullptr }, bIsArchMeshActor{ false }, LeftClickAction{ nullptr }, ToggleVisibilityAction{ nullptr }, MeshGeneratorMappingContext{ nullptr }, TogglePawnAction{ nullptr }, PawnIndex{ -1 }, WallGeneratorMappingContext{ nullptr }, SplineWallIndex{ 0 }, bToggleInputContext { true }, CurrentMappingContext{ nullptr } {
	PawnReferences.Add(APerspectivePawn::StaticClass());
	PawnReferences.Add(AOrthographicPawn::StaticClass());
	PawnReferences.Add(AIsometricPawn::StaticClass());
}

void AInteractiveArchController::BeginPlay() {
	Super::BeginPlay();

	SetShowMouseCursor(true);

	MeshGeneratorSelectionWidget = CreateWidget<USelectionWidget>(this, SelectionWidgetClass, TEXT("Selection MeshGeneratorSelectionWidget"));
	
	MeshGeneratorSelectionWidget->ScrollBox1->OnMeshAssetReceived.BindUFunction(this, "HandleMeshSelection");
	MeshGeneratorSelectionWidget->ScrollBox1->OnMaterialAssetReceived.BindUFunction(this, "HandleMaterialSelection");
	MeshGeneratorSelectionWidget->ScrollBox1->OnTextureAssetReceived.BindUFunction(this, "HandleTextureSelection");

	MeshGeneratorSelectionWidget->ScrollBox2->OnMeshAssetReceived.BindUFunction(this, "HandleMeshSelection");
	MeshGeneratorSelectionWidget->ScrollBox2->OnMaterialAssetReceived.BindUFunction(this, "HandleMaterialSelection");
	MeshGeneratorSelectionWidget->ScrollBox2->OnTextureAssetReceived.BindUFunction(this, "HandleTextureSelection");

	MeshGeneratorSelectionWidget->ScrollBox3->OnMeshAssetReceived.BindUFunction(this, "HandleMeshSelection");
	MeshGeneratorSelectionWidget->ScrollBox3->OnMaterialAssetReceived.BindUFunction(this, "HandleMaterialSelection");
	MeshGeneratorSelectionWidget->ScrollBox3->OnTextureAssetReceived.BindUFunction(this, "HandleTextureSelection");

	// Print Widget
	PrintWidget = CreateWidget<UUserWidget>(this, PrintWidgetClass);
	//Help Widget
	CommandWidget = CreateWidget<UUserWidget>(this, CommandWidgetClass);

	SwitchModeWidget = CreateWidget<UUserWidget>(this, SwitchModeWidgetClass);
	SwitchModeWidget->AddToViewport(5);

	SetInputMode(InputMode);

	HandleTogglePawn();

	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	Notification.AddUFunction(this, "PrintMessageOnViewPort");
	if (SplineType) {
		AWallSpline* WallSpline = NewObject<AWallSpline>(this, SplineType, TEXT("Wall Spline 0"));
		ArrayWallSpline.Add(WallSpline);
		Notification.Broadcast(FString{ "New Wall Spline Started" });
	}

	BindToggleMode();
}

void AInteractiveArchController::SetupInputComponent() {
	Super::SetupInputComponent();

	SetupSwitchInput();
	SetupMeshGeneratorInput();
	SetupWallGeneratorInput();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) {
		Subsystem->AddMappingContext(MeshGeneratorMappingContext, 0);
		Subsystem->AddMappingContext(SwitchMappingContext, 0);
		CurrentMappingContext = MeshGeneratorMappingContext;
	}
}

void AInteractiveArchController::HandleLeftClick() {
	if (!MeshGeneratorSelectionWidget->IsInViewport()) {
		MeshGeneratorSelectionWidget->AddToViewport();
	}

	if (MeshGeneratorSelectionWidget->ScrollBox1->ScrollBoxAssetType == EAssetType::MeshData) {
		MeshGeneratorSelectionWidget->ScrollBox1->SetVisibility(ESlateVisibility::Visible);
		MeshGeneratorSelectionWidget->ScrollBox2->SetVisibility(ESlateVisibility::Hidden);
		MeshGeneratorSelectionWidget->ScrollBox3->SetVisibility(ESlateVisibility::Hidden);
	} 
	else if (MeshGeneratorSelectionWidget->ScrollBox2->ScrollBoxAssetType == EAssetType::MeshData) {
		MeshGeneratorSelectionWidget->ScrollBox2->SetVisibility(ESlateVisibility::Visible);
		MeshGeneratorSelectionWidget->ScrollBox1->SetVisibility(ESlateVisibility::Hidden);
		MeshGeneratorSelectionWidget->ScrollBox3->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (MeshGeneratorSelectionWidget->ScrollBox3->ScrollBoxAssetType == EAssetType::MeshData) {
		MeshGeneratorSelectionWidget->ScrollBox3->SetVisibility(ESlateVisibility::Visible);
		MeshGeneratorSelectionWidget->ScrollBox1->SetVisibility(ESlateVisibility::Hidden);
		MeshGeneratorSelectionWidget->ScrollBox2->SetVisibility(ESlateVisibility::Hidden);
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

					MeshGeneratorSelectionWidget->SetVisibility(ESlateVisibility::Visible);
					MeshGeneratorSelectionWidget->ScrollBox1->SetVisibility(ESlateVisibility::Visible);
					MeshGeneratorSelectionWidget->ScrollBox2->SetVisibility(ESlateVisibility::Visible);
					MeshGeneratorSelectionWidget->ScrollBox3->SetVisibility(ESlateVisibility::Visible);

					auto BoundingBox = Cast<AArchMeshActor>(CurrentHitActor)->GetStaticMeshComponent()->GetStaticMesh()->GetBoundingBox();
					auto Offset = BoundingBox.Max.Z;
					LastHitLocation = CurrentHitActor->GetActorLocation() - FVector(0, 0, Offset);
				}
				else {
					bIsArchMeshActor = false;

					MeshGeneratorSelectionWidget->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}
}

void AInteractiveArchController::HandleTabKey() {	
	if (MeshGeneratorSelectionWidget->IsInViewport()) {
		ESlateVisibility SlateVisibility = MeshGeneratorSelectionWidget->GetVisibility();

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

		MeshGeneratorSelectionWidget->SetVisibility(SlateVisibility);
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

		MeshGeneratorSelectionWidget->ScrollBox1->SetVisibility(ESlateVisibility::Visible);
		MeshGeneratorSelectionWidget->ScrollBox2->SetVisibility(ESlateVisibility::Visible);
		MeshGeneratorSelectionWidget->ScrollBox3->SetVisibility(ESlateVisibility::Visible);

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

void AInteractiveArchController::SetupMeshGeneratorInput() {
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	LeftClickAction = NewObject<UInputAction>(this);
	LeftClickAction->ValueType = EInputActionValueType::Boolean;
	ToggleVisibilityAction = NewObject<UInputAction>(this);
	ToggleVisibilityAction->ValueType = EInputActionValueType::Boolean;

	MeshGeneratorMappingContext = NewObject<UInputMappingContext>(this);
	MeshGeneratorMappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);
	MeshGeneratorMappingContext->MapKey(ToggleVisibilityAction, EKeys::Tab);

	EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleLeftClick);
	EnhancedInputComponent->BindAction(ToggleVisibilityAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleTabKey);
}

void AInteractiveArchController::SetupSwitchInput() {
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	TogglePawnAction = NewObject<UInputAction>(this);
	TogglePawnAction->ValueType = EInputActionValueType::Boolean;

	SwitchMappingContext = NewObject<UInputMappingContext>(this);
	SwitchMappingContext->MapKey(TogglePawnAction, EKeys::P);

	EnhancedInputComponent->BindAction(TogglePawnAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleTogglePawn);
}

void AInteractiveArchController::SetupWallGeneratorInput() {
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	check(EIC);

	auto* WallBuilderLeftClickAction = NewObject<UInputAction>(this, TEXT("Mouse Left Click"));
	WallBuilderLeftClickAction->ValueType = EInputActionValueType::Boolean;
	auto* RightClickAction = NewObject<UInputAction>(this, TEXT("Mouse Right Click"));
	RightClickAction->ValueType = EInputActionValueType::Boolean;
	auto* SelectNextWallAction = NewObject<UInputAction>(this, TEXT("Select Next Wall Key"));
	SelectNextWallAction->ValueType = EInputActionValueType::Boolean;
	auto* SelectPreviousWallAction = NewObject<UInputAction>(this, TEXT("Select Previous Wall Key"));
	SelectPreviousWallAction->ValueType = EInputActionValueType::Boolean;
	auto* DestroySplineWallAction = NewObject<UInputAction>(this, TEXT("Destroy Spline Wall Action"));
	DestroySplineWallAction->ValueType = EInputActionValueType::Boolean;
	auto* DeleteLastSplineWallAction = NewObject<UInputAction>(this, TEXT("Delete Last Spline Wall Action"));
	DeleteLastSplineWallAction->ValueType = EInputActionValueType::Boolean;

	WallGeneratorMappingContext = NewObject<UInputMappingContext>(this, TEXT("Mapping Context"));

	WallGeneratorMappingContext->MapKey(WallBuilderLeftClickAction, EKeys::LeftMouseButton);
	WallGeneratorMappingContext->MapKey(RightClickAction, EKeys::RightMouseButton);
	WallGeneratorMappingContext->MapKey(SelectNextWallAction, EKeys::L);
	WallGeneratorMappingContext->MapKey(SelectPreviousWallAction, EKeys::J);
	WallGeneratorMappingContext->MapKey(DestroySplineWallAction, EKeys::X);
	WallGeneratorMappingContext->MapKey(DeleteLastSplineWallAction, EKeys::Z);

	EIC->BindAction(WallBuilderLeftClickAction, ETriggerEvent::Completed, this, &AInteractiveArchController::LeftClickHandle);
	EIC->BindAction(RightClickAction, ETriggerEvent::Completed, this, &AInteractiveArchController::RightClickHandle);
	EIC->BindAction(SelectPreviousWallAction, ETriggerEvent::Completed, this, &AInteractiveArchController::SelectPreviousWallHandle);
	EIC->BindAction(SelectNextWallAction, ETriggerEvent::Completed, this, &AInteractiveArchController::SelectNextWallHandle);
	EIC->BindAction(DestroySplineWallAction, ETriggerEvent::Completed, this, &AInteractiveArchController::DestroySplineWallHandle);
	EIC->BindAction(DeleteLastSplineWallAction, ETriggerEvent::Completed, this, &AInteractiveArchController::DeleteLastSplineWallHandle);
}

void AInteractiveArchController::LeftClickHandle(const FInputActionValue& ActionValue) {
	bool Click = ActionValue.Get<bool>();

	FHitResult HitResult{};
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);

	if (HitResult.bBlockingHit) {
		ArrayWallSpline[SplineWallIndex]->CreateWall(HitResult.Location);
	}
}

void AInteractiveArchController::RightClickHandle(const FInputActionValue& ActionValue) {
	SplineWallIndex++;
	FString WallSplineName = "Wall Spline " + FString::FromInt(SplineWallIndex);

	if (SplineType) {
		AWallSpline* WallSpline = NewObject<AWallSpline>(this, SplineType, *WallSplineName);
		ArrayWallSpline.Add(WallSpline);
	}

	Notification.Broadcast(FString{ "New Wall Spline Started" });
}

void AInteractiveArchController::SelectPreviousWallHandle(const FInputActionValue& ActionValue) {
	if (SplineWallIndex > 0) {
		--SplineWallIndex;
	}

	Notification.Broadcast(FString{ "Selected Spline Wall: " } + FString::FromInt(SplineWallIndex));
}

void AInteractiveArchController::SelectNextWallHandle(const FInputActionValue& ActionValue) {
	if (SplineWallIndex < ArrayWallSpline.Num() - 1) {
		++SplineWallIndex;
	}

	Notification.Broadcast(FString{ "Selected Spline Wall: " } + FString::FromInt(SplineWallIndex));
}

void AInteractiveArchController::DestroySplineWallHandle(const FInputActionValue& ActionValue) {
	if (ArrayWallSpline[SplineWallIndex]) {
		ArrayWallSpline[SplineWallIndex]->DestroySpline();
	}

	Notification.Broadcast(FString{ "Destroyed Spline Wall: " } + FString::FromInt(SplineWallIndex));
}

void AInteractiveArchController::DeleteLastSplineWallHandle(const FInputActionValue& ActionValue) {
	ArrayWallSpline[SplineWallIndex]->RemoveLastSplinePoint();

	Notification.Broadcast(FString{ "Deleted Last Spline Point of Wall: " } + FString::FromInt(SplineWallIndex));
}

void AInteractiveArchController::DestroyAllSplineWall() {
	for (int i = 0; i < ArrayWallSpline.Num(); i++) {
		ArrayWallSpline[i]->DestroySpline();
	}

	Notification.Broadcast("Destroyed All Spline Walls");
}

void AInteractiveArchController::ToggleMappingContext() {
	if (auto* Subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {

		if (bToggleInputContext) {
			Subsytem->RemoveMappingContext(MeshGeneratorMappingContext);
			MeshGeneratorSelectionWidget->RemoveFromParent();

			if (WallGeneratorMappingContext) {
				Subsytem->AddMappingContext(WallGeneratorMappingContext, 0);
				CurrentMappingContext = WallGeneratorMappingContext;

				if (PrintWidget && CommandWidget) {
					PrintWidget->AddToViewport();
					CommandWidget->AddToViewport();
				}
			}

			bToggleInputContext = !bToggleInputContext;
		}
		else {
			Subsytem->RemoveMappingContext(WallGeneratorMappingContext);
			PrintWidget->RemoveFromParent();
			CommandWidget->RemoveFromParent();

			if (MeshGeneratorMappingContext) {
				Subsytem->AddMappingContext(MeshGeneratorMappingContext, 0);
				CurrentMappingContext = MeshGeneratorMappingContext;
			}

			bToggleInputContext = !bToggleInputContext;
		}
	}
}