// Fill out your copyright notice in the Description page of Project Settings.


#include "WallBuilderController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

void AWallBuilderController::BeginPlay() {
	Super::BeginPlay();

	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	if (SplineType) {
		AWallSpline* WallSpline = NewObject<AWallSpline>(this, SplineType, TEXT("Wall Spline 0"));
		ArrayWallSpline.Add(WallSpline);
	}
}

AWallBuilderController::AWallBuilderController() : LeftClickAction{ nullptr }, RightClickAction{ nullptr }, SelectPreviousWallAction{ nullptr }, SelectNextWallAction{ nullptr }, MappingContext { nullptr }, WallIndex{ 0 } {}

void AWallBuilderController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	check(EIC);

	LeftClickAction = NewObject<UInputAction>(this, TEXT("Mouse Left Click"));
	LeftClickAction->ValueType = EInputActionValueType::Boolean;
	RightClickAction = NewObject<UInputAction>(this, TEXT("Mouse Right Click"));
	RightClickAction->ValueType = EInputActionValueType::Boolean;
	SelectNextWallAction = NewObject<UInputAction>(this, TEXT("Select Next Wall Key"));
	SelectNextWallAction->ValueType = EInputActionValueType::Boolean;
	SelectPreviousWallAction = NewObject<UInputAction>(this, TEXT("Select Previous Wall Key"));
	SelectPreviousWallAction->ValueType = EInputActionValueType::Boolean;
	DestroySplineWallAction = NewObject<UInputAction>(this, TEXT("Destroy Spline Wall Action"));
	DestroySplineWallAction->ValueType = EInputActionValueType::Boolean;
	DeleteLastSplineWallAction = NewObject<UInputAction>(this, TEXT("Delete Last Spline Wall Action"));
	DeleteLastSplineWallAction->ValueType = EInputActionValueType::Boolean;

	MappingContext = NewObject<UInputMappingContext>(this, TEXT("Mapping Context"));

	MappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);
	MappingContext->MapKey(RightClickAction, EKeys::RightMouseButton);
	MappingContext->MapKey(SelectNextWallAction, EKeys::L);
	MappingContext->MapKey(SelectPreviousWallAction, EKeys::J);
	MappingContext->MapKey(DestroySplineWallAction, EKeys::X);
	MappingContext->MapKey(DeleteLastSplineWallAction, EKeys::Z);

	EIC->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AWallBuilderController::LeftClickHandle);
	EIC->BindAction(RightClickAction, ETriggerEvent::Completed, this, &AWallBuilderController::RightClickHandle);
	EIC->BindAction(SelectPreviousWallAction, ETriggerEvent::Completed, this, &AWallBuilderController::SelectPreviousWallHandle);
	EIC->BindAction(SelectNextWallAction, ETriggerEvent::Completed, this, &AWallBuilderController::SelectNextWallHandle);
	EIC->BindAction(DestroySplineWallAction, ETriggerEvent::Completed, this, &AWallBuilderController::DestroySplineWallHandle);
	EIC->BindAction(DeleteLastSplineWallAction, ETriggerEvent::Completed, this, &AWallBuilderController::DeleteLastSplineWallHandle);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext, 0);
}

void AWallBuilderController::LeftClickHandle(const FInputActionValue& ActionValue) {
	bool Click = ActionValue.Get<bool>();

	FHitResult HitResult{};
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);

	if (HitResult.bBlockingHit) {
		ArrayWallSpline[WallIndex]->CreateWall(HitResult.Location);
	}
}

void AWallBuilderController::RightClickHandle(const FInputActionValue& ActionValue) {
	WallIndex++;
	FString WallSplineName = "Wall Spline " + FString::FromInt(WallIndex);


	if (SplineType) {
		AWallSpline* WallSpline = NewObject<AWallSpline>(this, SplineType, *WallSplineName);
		ArrayWallSpline.Add(WallSpline);
	}
}

void AWallBuilderController::SelectPreviousWallHandle(const FInputActionValue& ActionValue) {
	if (WallIndex > 0) {
		WallIndex--;
	}
	return;
}

void AWallBuilderController::SelectNextWallHandle(const FInputActionValue& ActionValue) {
	if (WallIndex < ArrayWallSpline.Num() - 1) {
		WallIndex++;
	}
	return;
}

void AWallBuilderController::DestroySplineWallHandle(const FInputActionValue& ActionValue) {
	ArrayWallSpline[WallIndex]->DestroySpline();
}

void AWallBuilderController::DeleteLastSplineWallHandle(const FInputActionValue& ActionValue) {
	ArrayWallSpline[WallIndex]->RemoveLastSplinePoint();
}