// Fill out your copyright notice in the Description page of Project Settings.


#include "WallBuilderController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

AWallBuilderController::AWallBuilderController() {
	WallSpline = CreateDefaultSubobject<AWallSpline>(TEXT("WallSpline"));

	SetShowMouseCursor(true);
}

void AWallBuilderController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	check(EIC);

	ClickAction = NewObject<UInputAction>(this, TEXT("Mouse Click"));
	ClickAction->ValueType = EInputActionValueType::Boolean;

	MappingContext = NewObject<UInputMappingContext>(this, TEXT("Mapping Context"));

	MappingContext->MapKey(ClickAction, EKeys::LeftMouseButton);

	EIC->BindAction(ClickAction, ETriggerEvent::Completed, this, &AWallBuilderController::ClickHandle);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext, 0);
}

void AWallBuilderController::ClickHandle(const FInputActionValue& ActionValue) {
	bool Click = ActionValue.Get<bool>();

	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);

	WallSpline->CreateWall(HitResult.Location);
}
