

#include "OrthographicPawn.h"

// Sets default values
AOrthographicPawn::AOrthographicPawn() : OrthographicPawnMapping{ nullptr }, CameraMovementAction{ nullptr }, ZoomInOutAction{ nullptr },  CameraXRotationAction{ nullptr } {
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("OrthographicSpringArm"));
	SpringArm->SetupAttachment(SceneRoot);
	SpringArm->SetRelativeRotation(FRotator(-90.0, 0.0, 0.0));
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.0f;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("OrthographicCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	Camera->bUsePawnControlRotation = false;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

// Called when the game starts or when spawned
void AOrthographicPawn::BeginPlay() {
	Super::BeginPlay();
}

void AOrthographicPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOrthographicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	OrthographicPawnMapping = NewObject<UInputMappingContext>(this);

	CameraMovementAction = NewObject<UInputAction>(this);
	CameraMovementAction->ValueType = EInputActionValueType::Axis2D;

	ZoomInOutAction = NewObject<UInputAction>(this);
	ZoomInOutAction->ValueType = EInputActionValueType::Axis1D;

	CameraXRotationAction = NewObject<UInputAction>(this);
	CameraXRotationAction->ValueType = EInputActionValueType::Axis1D;

	UInputModifierSwizzleAxis* SwizzleAxisModifierAD = NewObject<UInputModifierSwizzleAxis>(this);
	SwizzleAxisModifierAD->Order = EInputAxisSwizzle::YXZ;
	UInputModifierNegate* MoveActionModifierNegate = NewObject<UInputModifierNegate>(this);

	FEnhancedActionKeyMapping& KeyW = OrthographicPawnMapping->MapKey(CameraMovementAction, EKeys::W);

	FEnhancedActionKeyMapping& KeyS = OrthographicPawnMapping->MapKey(CameraMovementAction, EKeys::S);
	KeyS.Modifiers.Add(MoveActionModifierNegate);

	FEnhancedActionKeyMapping& KeyD = OrthographicPawnMapping->MapKey(CameraMovementAction, EKeys::D);
	KeyD.Modifiers.Add(SwizzleAxisModifierAD);

	FEnhancedActionKeyMapping& KeyA = OrthographicPawnMapping->MapKey(CameraMovementAction, EKeys::A);
	KeyA.Modifiers.Add(SwizzleAxisModifierAD);
	KeyA.Modifiers.Add(MoveActionModifierNegate);

	OrthographicPawnMapping->MapKey(ZoomInOutAction, EKeys::MouseWheelAxis);
	OrthographicPawnMapping->MapKey(CameraXRotationAction, EKeys::MouseX);

	if (EIC) {
		EIC->BindAction(CameraMovementAction, ETriggerEvent::Triggered, this, &AOrthographicPawn::CameraMovement);
		EIC->BindAction(ZoomInOutAction, ETriggerEvent::Triggered, this, &AOrthographicPawn::CameraZoom);
		EIC->BindAction(CameraXRotationAction, ETriggerEvent::Triggered, this, &AOrthographicPawn::RotationX);
	}

	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		check(SubSystem);
		//SubSystem->ClearAllMappings();
		SubSystem->AddMappingContext(OrthographicPawnMapping, 0);
	}
}

void AOrthographicPawn::CameraMovement(const FInputActionValue& ActionValue) {
	FVector2D MovementScale = ActionValue.Get<FVector2D>();

	AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), MovementScale.X);
	AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), MovementScale.Y);
}

void AOrthographicPawn::CameraZoom(const FInputActionValue& ActionValue) {
	float ZoomScale = ActionValue.Get<float>();

	SpringArm->TargetArmLength -= ZoomScale * 25;
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, 250.0f, FLT_MAX);
}

void AOrthographicPawn::RotationX(const FInputActionValue& ActionValue) {
	float RotateScale = ActionValue.Get<float>();

	AddActorLocalRotation(FRotator{ 0.0, RotateScale, 0.0});
}