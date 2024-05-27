// Fill out your copyright notice in the Description page of Project Settings.


#include "IsometricPawn.h"

// Sets default values
AIsometricPawn::AIsometricPawn() : IsometricPawnMapping{ nullptr }, CameraLeftRotationAction{ nullptr }, CameraRightRotationAction{ nullptr }, ZoomInOutAction{ nullptr } {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(SceneRoot);
	SpringArm->SetRelativeRotation(FRotator{ -45.0, 45.0, 0.0 });
	SpringArm->TargetArmLength = 2500;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 5.0f;
	SpringArm->CameraRotationLagSpeed = 30.0f;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("IsometricCamera"));
	Camera->SetupAttachment(SpringArm, SpringArm->SocketName);
	Camera->AddRelativeRotation(FRotator{ 0, 0, 0 });

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	RotationSpeed = 2.0f;
	TargetRotationYawValue = 45.0f;
}

// Called when the game starts or when spawned
void AIsometricPawn::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AIsometricPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = SpringArm->GetRelativeRotation();
	FRotator TargetRotation = FRotator(CurrentRotation.Pitch, TargetRotationYawValue, CurrentRotation.Roll);
	SpringArm->SetRelativeRotation(FMath::Lerp(CurrentRotation, TargetRotation, DeltaTime));
}

// Called to bind functionality to input
void AIsometricPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	IsometricPawnMapping = NewObject<UInputMappingContext>(this);

	CameraLeftRotationAction = NewObject<UInputAction>(this);
	CameraLeftRotationAction->ValueType = EInputActionValueType::Boolean;

	CameraRightRotationAction = NewObject<UInputAction>(this);
	CameraRightRotationAction->ValueType = EInputActionValueType::Boolean;

	ZoomInOutAction = NewObject<UInputAction>(this);
	ZoomInOutAction->ValueType = EInputActionValueType::Axis1D;

	IsometricPawnMapping->MapKey(CameraLeftRotationAction, EKeys::Q);
	IsometricPawnMapping->MapKey(CameraRightRotationAction, EKeys::E);
	IsometricPawnMapping->MapKey(ZoomInOutAction, EKeys::MouseWheelAxis);

	if (EIC) {
		EIC->BindAction(CameraLeftRotationAction, ETriggerEvent::Completed, this, &AIsometricPawn::CameraLeftRotation);
		EIC->BindAction(CameraRightRotationAction, ETriggerEvent::Completed, this, &AIsometricPawn::CameraRightRotation);
		EIC->BindAction(ZoomInOutAction, ETriggerEvent::Triggered, this, &AIsometricPawn::CameraZoom);
	}

	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (SubSystem) {
			SubSystem->AddMappingContext(IsometricPawnMapping, 0);
		}
	}
}

void AIsometricPawn::CameraLeftRotation() {
	TargetRotationYawValue += 45;
	TargetRotationYawValue = FMath::Wrap(TargetRotationYawValue, -180.0f, 180.0f);
}

void AIsometricPawn::CameraRightRotation() {
	TargetRotationYawValue -= 45;
	TargetRotationYawValue = FMath::Wrap(TargetRotationYawValue, -180.0f, 180.0f);
}

void AIsometricPawn::CameraZoom(const FInputActionValue& ActionValue) {
	float value = ActionValue.Get<float>();

	SpringArm->TargetArmLength -= value * 50;
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, 1000, 3000);
}
