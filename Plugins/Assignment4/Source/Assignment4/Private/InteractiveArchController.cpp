// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveArchController.h"


void AInteractiveArchController::BeginPlay() {
	Super::BeginPlay();

	SetShowMouseCursor(true);

	UUserWidget* Widget = CreateWidget(this, SelectionWidget, TEXT("Selection Widget"));

	Widget->AddToViewport();
}

void AInteractiveArchController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	LeftClickAction = NewObject<UInputAction>(this, TEXT("LeftClickAction"));
	LeftClickAction->ValueType = EInputActionValueType::Boolean;

	InputMappingContext = NewObject<UInputMappingContext>(this, TEXT("InputMappingContext"));
	InputMappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);

	EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AInteractiveArchController::HandleLeftClick);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void AInteractiveArchController::HandleLeftClick() {
	FVector WorldLocation{}, WorldDirection{};

	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = WorldLocation + (WorldDirection * 10000.0);

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.bTraceComplex = true;

		FHitResult HitResult;

		//if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams)) {
		//	if (CurrentHitActor = HitResult.GetActor()) {
		//		LastHitLocation = HitResult.Location;

		//	}
		//}
	}
}